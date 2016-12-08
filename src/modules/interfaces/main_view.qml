//This is main view window
//You can add and change lines before and after <//start_inp..//end_inp..>
//Please do not touch this words
//Because this is beacons for parser

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

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Project1793. Main Window")

    //global signals:
    //wps_attack_module
    signal signal_Refresh_interfaces_list()
    signal signal_Refresh_WPS_list(string msg)
    signal signal_Stop_refreshing_WPS_list()
    signal signal_Start_WPS_attack(string interf, string essid, string bssid,
                                   int pixieState)
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
