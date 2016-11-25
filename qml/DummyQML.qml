import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: root
    Button {
        text: qsTr("Dummy BUTTON")
        width: 234
        height: 90
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -118
        anchors.verticalCenter: parent.verticalCenter
        onClicked: signalDummy()
    }
}
