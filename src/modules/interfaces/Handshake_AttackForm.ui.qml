import QtQuick 2.4

Item {
    id: item1
    width: 400
    height: 400

    Text {
        id: text1
        text: qsTr("Still in development...")
        anchors.right: parent.right
        anchors.rightMargin: 115
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 344
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        font.pixelSize: 18
    }
}
