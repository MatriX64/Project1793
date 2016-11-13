import QtQuick 2.4
import QtQuick.Controls 2.0

Item {
    width: 400
    height: 400
    property alias testButton: testButton
    property alias image1: image1

    Image {
        id: image1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        transformOrigin: Item.Center
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "../../../../Pictures/summer.jpeg"

        Button {
            id: testButton
            x: 150
            y: 8
            text: qsTr("Button")
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
