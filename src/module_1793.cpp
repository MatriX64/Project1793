#include "include/module_1793.h"

Module_1793::Module_1793(const QString& moduleName, const QString &fileName) : mainModel(new Model_1793(model))
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
    QJsonObject resultObject;
    QJsonObject viewBefore;
    QString currentModulesPath = QString(mainModel->qmlTabView);
    for (int i = modulePath.count(); i >= 0 ; i--)
    {
        if (!currentModulesPath.contains("BabView" + QString::number(i)))
        {
            if (i == modulePath.count())
            {
                QJsonObject moduleAnchor;
                moduleAnchor.insert("Anchors.fill", "parent");
                QJsonObject moduleClass;
                moduleClass.insert(file_name, moduleAnchor);
                QJsonObject moduleRectangle;
                moduleRectangle.insert("vectangle", moduleClass);
                moduleRectangle.insert("uitle", "qsTr(\"" + modulePath.at(i-1) + "\")");
                QJsonObject moduleTab;
                moduleTab.insert("Tab", moduleRectangle);

                viewBefore = moduleTab;

                viewBefore.insert("Anchors.fill", "parent");
            } else
            {
                resultObject.remove("BabView" + QString::number(i+1));

                viewBefore.insert("Anchors.fill", "parent");
                resultObject.insert("BabView" + QString::number(i), viewBefore);

                viewBefore = resultObject;
            }
        }
    }

    QJsonObject obj1;
    QJsonObject obj3;
    obj1.insert("Ena", "Sana");
    obj1.insert("eka", "sanka");

    obj3.insert("Uva", obj1);

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
