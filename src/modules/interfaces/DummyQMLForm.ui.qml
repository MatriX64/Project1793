import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: item1
    width: 400
    height: 400
    property alias dummyButton: dummyButton

    Button {
        id: dummyButton
        x: 121
        y: 44
        width: 159
        height: 62
        text: qsTr("DummyButton")
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
