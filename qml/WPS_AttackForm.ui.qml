import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: item1
    width: 400
    height: 400
    property alias testButton: testButton

    Button {
        id: testButton
        x: 150
        y: 34
        width: 234
        height: 90
        text: qsTr("QML SIGNAL")
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -118
        anchors.verticalCenter: parent.verticalCenter
    }
}
