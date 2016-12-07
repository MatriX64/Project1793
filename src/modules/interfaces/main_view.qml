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
    minimumWidth: 500
    minimumHeight: 500
    title: qsTr("Project1793. Main Window")

    //global signals:
    //wps_attack_module
    signal signal_Refresh_interfaces_list()
    signal signal_Refresh_WPS_list(string msg)
    signal signal_Stop_refreshing_WPS_list()
    signal signal_Start_WPS_attack(string interf, string essid, string bssid)
    signal signal_Stop_WPS_attack()
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
                    TabView {
                        anchors.fill: parent
                        Tab {
                            title: qsTr("wps_attack")
                            WPS_Attack {
                                anchors.fill: parent
                            }
                        }
                    }
                }
                Tab {
                    title: qsTr("test_module")
                    DummyQML {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
//end_input
}
