//This is main view window
//You can add and change lines before and after <//start_inp..//end_inp..>
//Please do not touch this words
//Because this is beacons for parser

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: qsTr("Project1793. Main Window")

    //signals of modules here:
    signal qmlScream()
    signal signalDummy()

//start_input
    TabView {
        anchors.fill: parent
        Tab {
            title: qsTr("password_attacks")
            TabView {
                anchors.fill: parent
                Tab {
                    title: qsTr("wep/wpa/wpa2_attacks")
                    WPS_Attack {
                        anchors.fill: parent
                    }
                }
            }
        }
        Tab {
            title: qsTr("crypt_test")
            DummyQML {
                anchors.fill: parent
            }
        }
    }
//end_input
}
