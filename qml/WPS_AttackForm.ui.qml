import QtQuick 2.4

Item {
    width: 400
    height: 400

    Image {
        id: image1
        transformOrigin: Item.Center
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "../../../../Pictures/summer.jpeg"
    }
}
