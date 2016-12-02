#include "initializer_1793.h"

Initializer_1793::Initializer_1793(QObject *parent) : QObject(parent)
{

}

void Initializer_1793::initialize()
{
    if (!check_packages())
        return;

    if (!generate_main_view())
        return;

    emit finish_initialization();
}

bool Initializer_1793::check_packages()
{
    QProcess chpaths(this);
    chpaths.start("chmod +x " + QCoreApplication::applicationDirPath() + "/scripts/checkpkgs.sh");
    chpaths.waitForFinished();

    chpaths.start("/bin/bash " + QCoreApplication::applicationDirPath() +  "/scripts/checkpkgs.sh");
    chpaths.waitForReadyRead();
    QString chpathsOutput = QTextCodec::codecForMib(106)->toUnicode(chpaths.readAll());

    chpaths.waitForFinished();
    if (!QString::compare(chpathsOutput, "complete\n", Qt::CaseSensitive))
    {
        Logger_1793::write_log_file(LogCriticalMsg, "Проверка наличия необходимых для запуска данных прошла успешно");
        return true;
    } else if (!QString::compare(chpathsOutput, "nroot\n", Qt::CaseSensitive))
    {
        Logger_1793::write_log_file(LogInfoMsg, "Ошибка. Пожалуйста, запустите программу от root пользователя");
        emit critical_error();
        return false;
    } else if (!QString::compare(chpathsOutput, "adenied\n", Qt::CaseSensitive))
    {
        Logger_1793::write_log_file(LogInfoMsg, "Ошибка. Не получены необходимые права доступа");
        emit critical_error();
        return false;
    } else
    {
        Logger_1793::write_log_file(LogInfoMsg, "Ошибка при работе с checkpkgs.sh скриптом");
        emit critical_error();
        return false;
    }
    return true;
}

bool Initializer_1793::generate_main_view()
{
    add_module_layouts();
    if (!set_modules())
        return false;
    else
        return true;
}

//custom TabView path
void Initializer_1793::add_module_layouts()
{
    Initializer_1793::new_module_layout("password_attacks|wep/wpa/wpa2_attacks|wps_attack", "WPS_Attack");
    Initializer_1793::new_module_layout("password_attacks|test_module", "DummyQML");
}

void Initializer_1793::new_module_layout(const QString &moduleName, const QString &fileName)
{
    if (fileName.contains(" ") || fileName.contains("\\") || fileName.contains(QRegularExpression("\\d")))
    {
        qDebug() << "Error in file name";
        return;
    } else if (Model_1793::modulesList.contains(fileName))
    {
        qDebug() << "MainView already contains module " + fileName;
        return;
    }

    Model_1793::modulesList.append(fileName);

    QStringList modulePath;
    modulePath = moduleName.split("|");

    for (int i = 0; i < modulePath.count(); i++) //switch modules paths
    {
        if (i == modulePath.count() - 1) //if it's last path
        {
            QString pathTale;

            for (int j = 0; j <= i; j++) //make value
            {
                pathTale.append(modulePath.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);

            if (!(Model_1793::qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")) && (!Model_1793::qmlTabView.value(Model_1793::qmlTabView.key(pathTale)).compare(pathTale))) && (!(Model_1793::qmlTabView.contains(QString::number(i)) && (!Model_1793::qmlTabView.value(QString::number(i)).compare(pathTale)))))
            { //if there isn't key: number, value: keyValue or there isn't key: number+string, value: keyValue then insert key: number+string, value: keyValue
                Model_1793::qmlTabView.insertMulti(QString::number(i) + " " + fileName, pathTale);
            }
        } else //if it isn't last path
        {
            QString pathTale;
            for (int j = 0; j <= i; j++) //make value
            {
                pathTale.append(modulePath.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);

            if (Model_1793::qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")))
            { //if there is key: number+string then replace it with key: number, value: keyValue
                Model_1793::qmlTabView.remove(Model_1793::qmlTabView.key(pathTale));
                Model_1793::qmlTabView.insert(QString::number(i), pathTale);
            } else if (!(Model_1793::qmlTabView.contains(QString::number(i)) && (!Model_1793::qmlTabView.value(QString::number(i)).compare(pathTale))))
            { //else if there isn't key: number, value: keyValue
                Model_1793::qmlTabView.insertMulti(QString::number(i), pathTale);
            }
        }
    }
}

bool Initializer_1793::set_modules()
{
    QMap<QString,QString> view = Model_1793::qmlTabView;
    QRegularExpression captureKeyD("\\d+");
    QRegularExpression captureKeyW("(\\S+)(\\w+)");

    //find max column number
    QList<QString> keysList = view.keys();
    int maxElement = 0;
    for (int i = 0; i < keysList.count(); i++)
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

    //construct a json hierarchy, which will be the QML TabView hierarchy
    QMap <QString,QJsonObject> mainHierarchy;
    for (int i = maxElement; i >= 0; i--)
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
                QJsonObject moduleClass;
                moduleClass.insert("0title", "qsTr(\"" + parentPath.last() + "\")");
                moduleClass.insert("3TabView", mainHierarchy.value(tabName.at(j)));
                currentTabs.insertMulti(pathTale, moduleClass);
                mainHierarchy.remove(tabName.at(j));
            }

            {
                QJsonObject moduleClass;
                moduleClass.insert("0title", "qsTr(\"" + parentPath.last() + "\")");
                moduleClass.insert("3TabView", mainHierarchy.value(tabName.at(j)));
                currentTabs.insertMulti("|", moduleClass);
                mainHierarchy.remove(tabName.at(j));
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

            mainHierarchy.insertMulti(tabKeysList.at(k), tabView);
        }
    }
    //this object will contain full TabView hierarchy
    QJsonObject root;
    root.insert("3TabView", mainHierarchy.first());
    //qDebug() << "ColumnCount:" << maxElement;
    //qDebug() << keysList;

    //convert json to qstring
    QJsonDocument doc(root);
    QByteArray testViewJson = doc.toJson();
    QString tabViewString = QString(testViewJson);

    //begin of removing excess symbols(spaces, slashes etc...), which json hierarchy contains
    //and replacing some metawords
    tabViewString.remove(0, 1);
    tabViewString.chop(2);

    tabViewString.remove("\"");
    tabViewString.remove(",");

    QRegularExpression changeExp;
    changeExp.setPattern("\\dTabView:");
    tabViewString.replace(changeExp, "TabView");
    changeExp.setPattern("\\dtitle:");
    tabViewString.replace(changeExp, "title:");
    changeExp.setPattern("\\dTab\\d:");
    tabViewString.replace(changeExp, "Tab");
    changeExp.setPattern("\\danchors.fill:");
    tabViewString.replace(changeExp, "anchors.fill:");
    changeExp.setPattern(":\\s{");
    tabViewString.replace(changeExp, " {");
    changeExp.setPattern("\\\\");
    tabViewString.replace(changeExp, "\"");

    //read main QML file
    QFile main_view_file(QCoreApplication::applicationDirPath() + "/src/modules/interfaces/main_view.qml");
    if (!main_view_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Logger_1793::write_log_file(LogCriticalMsg, "Cannot open main_view.qml file");
        emit critical_error();
        return false;
    }
    QString main_view_text = main_view_file.readAll();
    main_view_file.close();

    //compare current state of TabView hierarchy with just created
    QRegularExpression regProcessMainViewText("((?<=//start_input)(?s)(.*)(?=//end_input))");
    QRegularExpressionMatch match = regProcessMainViewText.match(main_view_text);

    //if it mismatch then replace it with just created hierarhy
    if (match.captured(0).compare(tabViewString))
    {
        main_view_text.replace(regProcessMainViewText, tabViewString);
        if (!main_view_file.open(QIODevice::WriteOnly | QIODevice::Unbuffered))
        {
            Logger_1793::write_log_file(LogCriticalMsg, "Cannot write to main_view.qml file");
            emit critical_error();
            return false;
        }
        QByteArray text = main_view_text.toUtf8();
        main_view_file.write(text);
        main_view_file.close();
        qDebug() << "main_view.qml was rewrited";
    }
    //qDebug() << "TabView created successfully";

    return true;
}
