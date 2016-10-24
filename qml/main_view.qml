import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: "Project1793. Главное окно"
    //start_input
    TabView {
        anchors.fill: parent
        Tab {
            title: qsTr("FirstLabel")
            Rectangle {
                anchors.fill: parent
            }
        }
        Tab {
            title: qsTr("SecondLabel")
            Rectangle {
                anchors.fill: parent
                TabView {
                    anchors.fill: parent
                    Tab {
                        title: qsTr("FirstLabeFirst")
                        Rectangle {
                            anchors.fill: parent
                        }
                    }
                    Tab {
                        title: qsTr("SecondLabelSecond")
                        Rectangle {
                            anchors.fill: parent
                            WpsAttackModule {

                            }
                        }
                    }
                }
            }
        }
    }

    //end_input
}
