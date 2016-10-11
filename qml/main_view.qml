import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: "Project1793. Главное окно"

    Text {
        text: qsTr("Тестовое сообщение....")
    }

    signal quit_signal()
    Button {
        anchors.centerIn: parent
        text: qsTr("Главное окно!")
        onClicked: root.quit_signal()
    }
}
