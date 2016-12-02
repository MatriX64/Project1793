import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: item1
    width: 400
    height: 400
    property alias wpsStdOut: wpsStdOut
    property alias wpsRefreshInterfacesList: wpsRefreshInterfacesList
    property alias wpsInterfacesList: wpsInterfacesList
    property alias wpsStopAttack: wpsStopAttack
    property alias wpsStopRefreshingNetworksList: wpsStopRefreshingNetworksList
    property alias wpsRefreshNetworksList: wpsRefreshNetworksList
    property alias wpsStartAttack: wpsStartAttack
    property alias wpsNetworksList: wpsNetworksList

    Button {
        id: wpsStartAttack
        text: qsTr("Start attack")
        anchors.right: wpsStopAttack.left
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: wpsRefreshNetworksList.bottom
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        anchors.topMargin: 6
    }

    ListView {
        id: wpsNetworksList
        anchors.right: wpsStdOut.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 60
        anchors.rightMargin: 6
        anchors.bottomMargin: 86
        boundsBehavior: Flickable.DragAndOvershootBounds
        flickableDirection: Flickable.VerticalFlick
        model: wpsListModel
        delegate: wpsNetworksListDelegate
    }

    TextArea {
        id: wpsStdOut
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        font.pointSize: 15
        anchors.topMargin: 25
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.leftMargin: 248
        textColor: "#891212"
    }

    Button {
        id: wpsStopAttack
        x: 123
        width: 119
        text: qsTr("Stop attack")
        anchors.top: wpsStopRefreshingNetworksList.bottom
        anchors.topMargin: 6
        anchors.right: wpsStdOut.left
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }

    Button {
        id: wpsRefreshNetworksList
        text: qsTr("Refresh")
        anchors.right: wpsStopRefreshingNetworksList.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: wpsNetworksList.bottom
        anchors.bottomMargin: 47
        anchors.leftMargin: 8
        anchors.rightMargin: 6
        anchors.topMargin: 6
    }

    ComboBox {
        id: wpsInterfacesList
        anchors.top: parent.top
        anchors.right: wpsRefreshInterfacesList.left
        anchors.bottom: wpsNetworksTitle.top
        anchors.left: parent.left
        anchors.bottomMargin: 6
        anchors.leftMargin: 8
        anchors.rightMargin: 6
        anchors.topMargin: 8
        model: interfacesListModel
    }

    Text {
        id: wpsSelectedNetwork
        text: qsTr("Selected network: " + networkName)
        anchors.bottom: wpsStdOut.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 3
        anchors.leftMargin: 248
        font.pixelSize: 12
    }

    Text {
        id: wpsNetworksTitle
        x: 8
        y: 40
        color: "#0b008d"
        text: qsTr("Networks with WPS list:")
        font.pixelSize: 12
    }

    Button {
        id: wpsStopRefreshingNetworksList
        text: qsTr("Stop refreshing")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 47
        anchors.left: parent.left
        anchors.leftMargin: 123
        anchors.top: wpsNetworksList.bottom
        anchors.topMargin: 6
        anchors.right: wpsStdOut.left
        anchors.rightMargin: 6
    }

    Button {
        id: wpsRefreshInterfacesList
        x: 173
        y: 8
        width: 69
        height: 26
        text: qsTr("Refresh")
        anchors.right: wpsStdOut.left
        anchors.rightMargin: 6
    }
}

