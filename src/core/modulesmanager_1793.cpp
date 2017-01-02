/*
 * Copyright (c) 2016, MatriXSan <matrix3sai@gmail.com>
 *
 *  This file is part of Project1793.
 *
 *  Project1793 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project1793 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Project1793.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "modulesmanager_1793.h"

ModulesManager_1793::ModulesManager_1793(QObject *parent) :  QObject(parent)
{

}

ModulesManager_1793::~ModulesManager_1793()
{
    for (int i = 0; i < modulesList.count(); i++)
    {
        modulesList.at(i)->terminate_module();
        delete (modulesList.at(i));
    }
}

void ModulesManager_1793::add_new_module(Module_1793* module, const QString &moduleName, const QString &modulePath)
{

    if (moduleName.contains(" ") || moduleName.contains("\\") || moduleName.contains(QRegularExpression("\\d")))
    {
        qDebug() << "Error in file name";
        return;
    } /*else if (modulesNamesList.contains(moduleName))
    {
        qDebug() << "MainView already contains module " + moduleName;
        return;
    }*/

    modulesNamesList.append(moduleName);
    modulesList.append(module);

    QStringList modulePathsList;
    modulePathsList = modulePath.split("|");

    for (int i = 0; i < modulePathsList.count(); i++) //switch modules paths
    {
        if (i == modulePathsList.count() - 1) //if it's last path
        {
            QString pathTale;

            for (int j = 0; j <= i; j++) //make value
            {
                pathTale.append(modulePathsList.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);

            if (!(qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")) && (!qmlTabView.value(qmlTabView.key(pathTale)).compare(pathTale))) && (!(qmlTabView.contains(QString::number(i)) && (!qmlTabView.value(QString::number(i)).compare(pathTale)))))
            { //if there isn't key: number, value: keyValue or there isn't key: number+string, value: keyValue then insert key: number+string, value: keyValue
                qmlTabView.insertMulti(QString::number(i) + " " + moduleName, pathTale);
            }
        } else //if it isn't last path
        {
            QString pathTale;
            for (int j = 0; j <= i; j++) //make value
            {
                pathTale.append(modulePathsList.at(j));
                pathTale.append("|");
            }
            pathTale.chop(1);

            if (qmlTabView.key(pathTale).contains(QRegularExpression(QString::number(i) + "\\s\\w")))
            { //if there is key: number+string then replace it with key: number, value: keyValue
                qmlTabView.remove(qmlTabView.key(pathTale));
                qmlTabView.insert(QString::number(i), pathTale);
            } else if (!(qmlTabView.contains(QString::number(i)) && (!qmlTabView.value(QString::number(i)).compare(pathTale))))
            { //else if there isn't key: number, value: keyValue
                qmlTabView.insertMulti(QString::number(i), pathTale);
            }
        }
    }
}

QByteArray ModulesManager_1793::set_modules()
{
    QMap<QString,QString> view = qmlTabView;
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
                QJsonObject moduleParameters;
                moduleParameters.insert("0anchors.fill", "parent");
                QJsonObject moduleClass;
                moduleClass.insert(keysWithStrings.value(tabName.at(j)), moduleParameters);
                moduleClass.insert("0title", "qsTr(\"" + parentPath.last() + "\")");
                moduleClass.insert("1active", "true");
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
    changeExp.setPattern("\\dactive:");
    tabViewString.replace(changeExp, "active:");
    changeExp.setPattern(":\\s{");
    tabViewString.replace(changeExp, " {");
    changeExp.setPattern("\\\\");
    tabViewString.replace(changeExp, "\"");


    QString quickVersion = "2.7",
            quickWindowVersion = "2.2",
            quickControlsVersion = "1.4",
            modulesFolderPath = "\"qrc:/src/modules/interfaces\"",
            mainWindowDefaultWidth = "900",
            mainWindowDefaultHeight = "700",
            mainWindowMinimumWidth = "800",
            mainWindowMinimumHeight = "600",
            mainWindowTitle = "\"Project1793. Main Window\"";


    QByteArray mainViewData;
    mainViewData.append("import QtQuick " + quickVersion + "\nimport QtQuick.Window " + quickWindowVersion + "\nimport QtQuick.Controls " + quickControlsVersion + "\nimport " + modulesFolderPath + "\n\nWindow { \n    visible: true \n    id: root \n    width: " + mainWindowDefaultWidth + "\n    height: " + mainWindowDefaultHeight + "\n    minimumWidth: " + mainWindowMinimumWidth + "\n    minimumHeight: " + mainWindowMinimumHeight + "\n    title: qsTr(" + mainWindowTitle + ")\n");

    mainViewData.append(tabViewString);
    mainViewData.append("}");

    //qDebug() << qPrintable(QVariant(*model->systemData.mainViewComponent).toString());

    return mainViewData;
}

void ModulesManager_1793::start_modules(Model_1793* model)
{
    for (int i = 0; i < modulesList.count(); i++)
    {
        modulesList.at(i)->initialize_module(model);
        modulesList.at(i)->start_module();
    }
    qDebug() << WindowsManager_1793::getQmlRootObjects().count();
}
