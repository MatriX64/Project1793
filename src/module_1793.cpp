#include "include/module_1793.h"

Module_1793::Module_1793(const QString& moduleName)
{
    qDebug() << moduleName;
    add_module_to_layout(moduleName);
}

Module_1793::~Module_1793()
{

}

void Module_1793::add_module_to_layout(const QString& module_name)
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

    QString currentModulesPath;
    QRegularExpressionMatch regModulesMatch = regProcessMainViewText.match(main_view_text);
    currentModulesPath = regModulesMatch.captured(0);
    qDebug() << qPrintable(currentModulesPath);
    QTextStream modulePathView;
    foreach (const QString &str, modulePath) {
        QRegularExpression regCheckModule(str);
        if (regCheckModule.captureCount() == 0)
            ;

        //modulePathView << "\n";
        //for (int i = 0; i < tabCouner; i++)
            //modulePathView << "\t";
        qDebug() << str;

    }
    qDebug() << modulePath;
    //main_view_text.replace(regProcessMainViewText, "SANASANASANA");
    qDebug() << qPrintable(main_view_text);
}
