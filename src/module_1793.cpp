#include "include/module_1793.h"

Module_1793::Module_1793(const QString& moduleName, const QString &fileName) : mainModel(model)
{
    add_module_to_layout(moduleName, fileName);
}

Module_1793::~Module_1793()
{

}

void Module_1793::add_module_to_layout(const QString& module_name, const QString& file_name)
{
    QFile main_view_file("/home/san/Qt/Projects/Project1793/qml/main_view_2.qml");
    if (!main_view_file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QString main_view_text = main_view_file.readAll();
    main_view_file.close();
    QRegularExpression regProcessMainViewText("((?<=//start_input)(?s)(.*)(?=//end_input))");
    if (!regProcessMainViewText.isValid())
        return;

    QStringList modulePath;
    modulePath = module_name.split("|");
    //qDebug() << modulePath;

    /*****************************************/
    /*QJsonObject resultObject;
    QJsonObject viewBefore;
    QString currentModulesPath = QString(mainModel->qmlTabView);
    for (int i = modulePath.count()-1; i >= 0 ; i--)
    {
        if (!currentModulesPath.contains("3TabView" + QString::number(i)))
        {
            if (i == modulePath.count()-1)
            {
                QJsonObject moduleAnchor;
                moduleAnchor.insert("0anchors.fill", "parent");
                QJsonObject moduleClass;
                moduleClass.insert(file_name, moduleAnchor);
                moduleClass.insert("0title", "qsTr(\"" + modulePath.at(i) + "\")");
                QJsonObject moduleTab;
                moduleTab.insert("1Tab0", moduleClass);
                moduleTab.insert("0anchors.fill", "parent");
                viewBefore.insert("3TabView" + QString::number(i), moduleTab);
                resultObject = viewBefore;
            } else
            {
                resultObject.insert("0anchors.fill", "parent");
                viewBefore.insert("0title", "qsTr(\"" + modulePath.at(i) + "\")");
                resultObject.insert("1Tab0", viewBefore);
                resultObject.remove("3TabView" + QString::number(i+1));
                resultObject.insert("3TabView" + QString::number(i), resultObject);

                resultObject.remove("1Tab0");
                resultObject.remove("0anchors.fill");
                resultObject.remove("3TabView" + QString::number(i+1));

                viewBefore = resultObject;
            }
        }
    }*/
    QJsonObject resultObject;

    for (int i = 0; i < modulePath.count(); i++)
    {

        if (i == 0)
        {
            if (!(mainModel->qmlTabView.contains("0") && (!mainModel->qmlTabView.value("0").compare(modulePath.at(0)))))
                mainModel->qmlTabView.insertMulti("0", modulePath.at(0));
        } else if (i == modulePath.count() - 1)
        {
            QString pathTale;
            for (int j = 0; j <= i; j++)
            {
                pathTale.append(modulePath.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);
            QRegularExpression moduleKeyTest(QString::number(i) + " \\s");
            if (!moduleKeyTest.isValid())
                qDebug() << "Not Valid";
            if (!((mainModel->qmlTabView.key(pathTale).contains(moduleKeyTest) || (mainModel->qmlTabView.contains(QString::number(i)))) && (!mainModel->qmlTabView.value(QString::number(i)).compare(pathTale))))
                mainModel->qmlTabView.insertMulti(QString::number(i) + " " + file_name, pathTale);
        } else
        {
            QString pathTale;
            for (int j = 0; j <= i; j++)
            {
                pathTale.append(modulePath.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);
            if (!(mainModel->qmlTabView.contains(QString::number(i)) && (!mainModel->qmlTabView.value(QString::number(i)).compare(pathTale))))
                mainModel->qmlTabView.insertMulti(QString::number(i), pathTale);
        }
    }

    QJsonDocument doc(resultObject);
    QByteArray testViewJson = doc.toJson();
    QString str = QString(testViewJson);
    qDebug() << qPrintable(str);

    //str.remove(0, 1);
    //str.chop(2);

    /*****************************************/
    //QRegularExpressionMatch regModulesMatch = regProcessMainViewText.match(main_view_text);
    //currentModulesPath = regModulesMatch.captured(0);

    //main_view_text.replace(regProcessMainViewText, str);
    //qDebug() << qPrintable(currentModulesPath);

    //qDebug() << qPrintable(main_view_text);
}
