import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: qsTr("Project1793. Главное окно")
//start_input
    TabView {
        anchors.fill: parent
        Tab {
            title: qsTr("FirstLabel")
        }
        Tab {
            title: qsTr("SecondLabel")
            TabView {
                anchors.fill: parent
                Tab {
                    title: qsTr("FirstLabeFirst")
                }
                Tab {
                    title: qsTr("SecondLabelSecond")
                    WPS_Attack {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
//end_input
}
