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
            width: 200; height: 20
            Text { text: 'Name: ' + name }
            Text { text: 'Mac: ' + mac }

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
        signal_Refresh_WPS_list(interfaceName)
        wpsRefreshNetworksList.checkable = true
        wpsRefreshNetworksList.checked = true
        wpsRefreshNetworksList.enabled = false
        wpsInterfacesList.enabled = false
        wpsNetworksList.enabled = false
        console.log("Refreshing WPS list started")
    }

    function stop_refreshing_WPS_list() {
        signal_Stop_refreshing_WPS_list()
        wpsRefreshNetworksList.checked = false
        wpsRefreshNetworksList.checkable = false
        wpsRefreshNetworksList.enabled = true
        wpsInterfacesList.enabled = true
        wpsNetworksList.enabled = true
        console.log("Refreshing WPS list stopped")
    }

    function start_WPS_attack() {
        wpsStartAttack.checkable = true
        wpsStartAttack.checked = true
    }

    function stop_WPS_attack() {
        wpsStartAttack.checked = false
        wpsStartAttack.checkable = false
    }

    function append_stdout_text(message) {
        wpsStdOut.append(message)
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

    Component.onCompleted: {
        console.log("Moule WPS_Attack loaded")
    }
}
