import QtQuick 2.4
import QtQuick.Controls 1.4

WPS_AttackForm {
    objectName: "wpsAttackModule"

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
        signal_Stop_refreshing_WPS_list()
        wpsRefreshNetworksList.checkable = false
        wpsRefreshNetworksList.checked = false
        wpsStopRefreshingNetworksList.checkable = true
        wpsStopRefreshingNetworksList.checked = true
        wpsStopRefreshingNetworksList.enabled = false
    }

    function start_WPS_attack() {
        signal_Start_WPS_attack(interfaceName ,networkName, networkMac)
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
        signal_Stop_WPS_attack()
        wpsStartAttack.checkable = false
        wpsStartAttack.checked = false
        wpsStopAttack.checkable = true
        wpsStopAttack.checked = true
        wpsStopAttack.enabled = false
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
