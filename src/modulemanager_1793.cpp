#include "include/modulemanager_1793.h"

ModuleManager_1793::ModuleManager_1793()
{

}

ModuleManager_1793::~ModuleManager_1793()
{
    delete_modules();
    emit send_log_file(LogInfoMsg, "Менеджер модулей уничтожен");
}

void ModuleManager_1793::start()
{
    mainModel = model;
    check_paths();
    check_libs();
    emit send_log_file(LogInfoMsg, "Менеджер модулей запущен");
    add_modules();
    set_modules();
}

void ModuleManager_1793::check_paths()
{
    QProcess chpaths(this);
    chpaths.start("chmod +x " + app_dir.absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForFinished();

    chpaths.start("/bin/bash " + app_dir.absolutePath() + "/bin/scripts/chpaths.sh");
    chpaths.waitForReadyRead();
    QString chpathsOutput = QTextCodec::codecForMib(106)->toUnicode(chpaths.readAll());
    qDebug() << chpathsOutput;
    chpaths.waitForFinished();
    if (QString::compare(chpathsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogCriticalMsg, "Ошибка проверки целостности модулей");
        emit quit_critical_sender();
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия модулей прошла успешно");
    }
}

void ModuleManager_1793::check_libs()
{
    QProcess chlibs(this);
    chlibs.start("chmod +x " + app_dir.absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForFinished();

    chlibs.start("/bin/bash " + app_dir.absolutePath() + "/bin/scripts/chlibs.sh");
    chlibs.waitForReadyRead();
    QString chlibsOutput = QTextCodec::codecForMib(106)->toUnicode(chlibs.readAll());
    qDebug() << chlibsOutput;
    chlibs.waitForFinished();
    if (QString::compare(chlibsOutput, "complete\n", Qt::CaseSensitive))
    {
        emit send_log_file(LogWarningMsg, "Не удалось корректно выполнить скрипт " + app_dir.absolutePath() + "/bin/Scripts/chlibs.sh");
    } else
    {
        emit send_log_file(LogInfoMsg, "Проверка наличия библиотек прошла успешно");
    }
}

void ModuleManager_1793::add_modules()
{
    wps_attack_module = new WPS_Attack_module("password_attacks|wep/wpa/wpa2_attacks|wps_attack", "WPS_Attack");
    wps_attack_module2 = new WPS_Attack_module("password_attacks|wps_attack|save", "Uka");
    wps_attack_module3 = new WPS_Attack_module("password_attacks|wps_attack|uva", "Unawps");
}

void ModuleManager_1793::set_modules()
{
    //find max column
    QMap<QString,QString> view = mainModel->qmlTabView;
    QList<QString> keysList = view.keys();
    QRegularExpression captureKeyD("\\d+");
    QRegularExpression captureKeyW("(\\S+)(\\w+)");
    int maxElement = 0;
    for (int i = 0; i < keysList.count(); i++) //find max column number
    {
        QRegularExpressionMatch captureD = captureKeyD.match(keysList.at(i));
        if (captureD.hasMatch())
        {
            if (maxElement < captureD.captured(0).toInt())
                maxElement = captureD.captured(0).toInt();
        }
    }

    QMap<QString,QString> keysWithStrings;
    for (int i = 0; i < keysList.count(); i++) //replace keys contains strings with keys containes numbers only
    {
        QRegularExpressionMatch captureD = captureKeyD.match(keysList.at(i));
        if (captureD.hasMatch())
        {
              QRegularExpressionMatch captureW = captureKeyW.match(keysList.at(i));
              if (captureW.hasMatch())
              {
                  QList<QString> values = view.values(captureD.captured(0) + " " + captureW.captured(0));
                  for (int j = 0; j < values.count(); j++)
                  {
                       keysWithStrings.insertMulti(values.at(j), captureW.captured(0));
                       view.insertMulti(captureD.captured(0), values.at(j));
                  }
                  view.remove(captureD.captured(0) + " " + captureW.captured(0));
              }
        }
        keysList = view.keys();
    }

    QJsonObject resultObject;
    QMap <QString,QJsonObject> mainIerarchy;
    for (int i = maxElement; i >= 0; i--) //construct a json ierarchy
    {
        QList<QString> tabName = view.values(QString::number(i));
        QMap<QString,QJsonObject> currentTabs;
        for (int j = 0; j < tabName.count(); j++)
        {
            QStringList parentPath;
            parentPath = tabName.at(j).split("|");
            QString pathTale;
            for (int k = 0; k < parentPath.count() - 1; k++)
            {
                pathTale.append(parentPath.at(k));
                pathTale.append("|");
            }
            pathTale.chop(1);

            if (i != 0)
            {
                if (keysWithStrings.contains(tabName.at(j)))
                {
                    QJsonObject moduleAnchor;
                    moduleAnchor.insert("0anchors.fill", "parent");
                    QJsonObject moduleClass;
                    moduleClass.insert(keysWithStrings.value(tabName.at(j)), moduleAnchor);
                    moduleClass.insert("0title", "qsTr(\"" + parentPath.last() + "\")");
                    currentTabs.insertMulti(pathTale, moduleClass);
                } else
                {
                    qDebug() << "lil";
                }
            }
        }
        QList<QString> tabKeysList = currentTabs.uniqueKeys();
        for (int k = 0; k < tabKeysList.count(); k++)
        {
            QJsonObject tabView;
            int tabNumber = 0;
            QList<QJsonObject> tabsObjects = currentTabs.values(tabKeysList.at(k));
            tabView.insert("0anchors.fill", "parent");
            for (int n = 0; n < tabsObjects.count(); n++)
            {
                tabView.insert("1Tab" + QString::number(tabNumber), tabsObjects.at(n));
                tabNumber++;
            }
            tabView.insert("3TabView", tabView);
            for (int u = 0; u < tabNumber; u++)
            {
                tabView.remove("1Tab" + QString::number(u));
            }
            mainIerarchy.insertMulti(tabKeysList.at(k), tabView);
        }
    }
    qDebug() << mainIerarchy;
    qDebug() << "ColumnCount:" << maxElement;
    qDebug() << keysList;

    QJsonDocument doc(resultObject);
    QByteArray testViewJson = doc.toJson();
    QString str = QString(testViewJson);
    qDebug() << qPrintable(str);
}

void ModuleManager_1793::delete_modules()
{
    delete (wps_attack_module);
}
