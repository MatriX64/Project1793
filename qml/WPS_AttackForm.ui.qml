import QtQuick 2.4
import QtQuick.Controls 2.0

Item {
    width: 400
    height: 400
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
        source: "qrc:/images/summer.jpeg"
    }
}
