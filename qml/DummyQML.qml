import QtQuick 2.4

Item {
    id: testModule
    objectName: "dummyObject"

    DummyQMLForm {
        anchors.fill: parent
        dummyButton.onClicked: signalDummy()
    }
}
