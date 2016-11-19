import QtQuick 2.4

Item {
    width: 400
    height: 400

    AnimatedImage {
        id: image1
        width: 400
        height: 400
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/waves.gif"
    }
}
