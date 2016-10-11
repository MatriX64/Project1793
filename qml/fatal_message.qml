import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 500
    height: 100
    title: "Project1793. Ошибка"

    Text {
        text: qsTr("Фатальная ошибка. Смотрите лог файл")
    }

    signal quit_signal()
    Button {
        anchors.centerIn: parent
        text: qsTr("Ok")
        onClicked: root.quit_signal()
    }
}
