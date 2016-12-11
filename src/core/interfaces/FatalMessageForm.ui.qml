import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: item1
    width: 400
    height: 400
    property alias terminationButton: terminationButton

    Button {
        id: terminationButton
        y: 49
        height: 35
        text: qsTr("OK")
        anchors.right: parent.right
        anchors.rightMargin: 124
        anchors.left: parent.left
        anchors.leftMargin: 124
    }

    Text {
        id: criticalText
        y: 8
        height: 35
        color: "#ba3838"
        text: qsTr("Critical error. Please, check \"log\" file")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
    }
}
