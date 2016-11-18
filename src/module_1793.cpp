#include "include/module_1793.h"

Module_1793::Module_1793() : mainModel(model)
{

}

Module_1793::~Module_1793()
{

}

void Module_1793::add_module_to_layout(const QString& moduleName, const QString& fileName)
{
    if (fileName.contains(" "))
    {
        qDebug() << "Error in file name";
    }

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

            if (!(mainModel->qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")) && (!mainModel->qmlTabView.value(mainModel->qmlTabView.key(pathTale)).compare(pathTale))) && (!(mainModel->qmlTabView.contains(QString::number(i)) && (!mainModel->qmlTabView.value(QString::number(i)).compare(pathTale)))))
            { //if there isn't key: number, value: keyValue or there isn't key: number+string, value: keyValue then insert key: number+string, value: keyValue
                mainModel->qmlTabView.insertMulti(QString::number(i) + " " + fileName, pathTale);
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

            if (mainModel->qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")))
            { //if there is key: number+string then replace it with key: number, value: keyValue
                mainModel->qmlTabView.remove(mainModel->qmlTabView.key(pathTale));
                mainModel->qmlTabView.insert(QString::number(i), pathTale);
            } else if (!(mainModel->qmlTabView.contains(QString::number(i)) && (!mainModel->qmlTabView.value(QString::number(i)).compare(pathTale))))
            { //else if there isn't key: number, value: keyValue
                mainModel->qmlTabView.insertMulti(QString::number(i), pathTale);
            }
        }
    }   
}
