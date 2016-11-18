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
        source: "../../build-Project1793-Desktop_Qt_5_7_0_GCC_64bit-Debug/bin/images/waves.gif"
    }
}
