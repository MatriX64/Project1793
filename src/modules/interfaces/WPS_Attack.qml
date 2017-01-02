/*
 * Copyright (c) 2016,2017 sanmira32 <matrix3sai@gmail.com>
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

import QtQuick 2.4
import QtQuick.Controls 1.4

WPS_AttackForm {
    objectName: "wpsAttackModule"

    signal signal_Refresh_interfaces_list()
    signal signal_Refresh_WPS_list(string msg)
    signal signal_Stop_refreshing_WPS_list()
    signal signal_Start_WPS_attack(string interf, string essid, string bssid, int pixieState)
    signal signal_Stop_WPS_attack()

    property var networkName: ""
    property var networkMac: ""
    property var interfaceName: ""

    Component {
        id: wpsNetworksListDelegate
        Item {
            id: wrapper
            width: 200; height: 35
            Column {
                Text { text: 'Name: ' + name }
                Text { text: 'Mac: ' + mac }
            }

            states: State {
                name: "currentItem"
                when: wrapper.ListView.isCurrentItem
                PropertyChanges { target: wrapper; x: 20; }
            }
            transitions: Transition {
                NumberAnimation { properties: "x"; duration: 200 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    wrapper.ListView.view.currentIndex = index
                }
            }
            onStateChanged: {
                networkName = name
                networkMac = mac
            }
        }
    }

    function refresh_Interfaces_list() {
        signal_Refresh_interfaces_list()
    }

    function refresh_WPS_list() {
        networkName = ""
        networkMac = ""

        signal_Refresh_WPS_list(interfaceName)

        wpsProgressBar.indeterminate = true
        wpsRefreshNetworksList.checkable = true
        wpsRefreshNetworksList.checked = true
        wpsRefreshNetworksList.enabled = false
        wpsInterfacesList.enabled = false
        wpsNetworksList.enabled = false
        wpsRefreshInterfacesList.enabled = false
        wpsStartAttack.enabled = false
        wpsStopAttack.enabled = false
    }

    function stop_refreshing_WPS_list() {
        wpsRefreshNetworksList.checkable = false
        wpsRefreshNetworksList.checked = false
        wpsStopRefreshingNetworksList.checkable = true
        wpsStopRefreshingNetworksList.checked = true
        wpsStopRefreshingNetworksList.enabled = false
        signal_Stop_refreshing_WPS_list()
    }

    function start_WPS_attack() {
        signal_Start_WPS_attack(interfaceName ,networkName, networkMac, wpsPixieBox.currentIndex)
        wpsProgressBar.indeterminate = true
        wpsStartAttack.checkable = true
        wpsStartAttack.checked = true
        wpsStartAttack.enabled = false
        wpsRefreshNetworksList.enabled = false
        wpsInterfacesList.enabled = false
        wpsNetworksList.enabled = false
        wpsRefreshInterfacesList.enabled = false
        wpsStopRefreshingNetworksList.enabled = false
    }

    function stop_WPS_attack() {
        wpsStartAttack.checkable = false
        wpsStartAttack.checked = false
        wpsStopAttack.checkable = true
        wpsStopAttack.checked = true
        wpsStopAttack.enabled = false
        signal_Stop_WPS_attack()
    }

    function append_stdout_text(message) {
        wpsStdOut.append(message)
    }

    function show_all() {
        wpsProgressBar.indeterminate = false
        wpsRefreshNetworksList.checked = false
        wpsRefreshNetworksList.checkable = false
        wpsRefreshNetworksList.enabled = true
        wpsInterfacesList.enabled = true
        wpsNetworksList.enabled = true
        wpsRefreshInterfacesList.enabled = true
        wpsStartAttack.checkable = false
        wpsStartAttack.checked = false
        wpsStartAttack.enabled = true
        wpsStopAttack.checkable = false
        wpsStopAttack.checked = false
        wpsStopAttack.enabled = true
        wpsStopRefreshingNetworksList.checkable = false
        wpsStopRefreshingNetworksList.checked = false
        wpsStopRefreshingNetworksList.enabled = true
    }

    wpsInterfacesList.onCurrentTextChanged: {
        interfaceName = wpsInterfacesList.textAt(wpsInterfacesList.currentIndex)
    }
    wpsRefreshInterfacesList.onClicked: refresh_Interfaces_list()
    wpsStartAttack.onClicked: start_WPS_attack()
    wpsStopAttack.onClicked: stop_WPS_attack()
    wpsStopRefreshingNetworksList.onClicked: stop_refreshing_WPS_list()
    wpsRefreshNetworksList.onClicked: refresh_WPS_list()

    anchors.fill: parent
}
