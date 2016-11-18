import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    id: root
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    width: 512
    height: 288
    color: "transparent"
    flags: Qt.FramelessWindowHint
    title: "Project1793. Starting"

    LauncherViewForm {
        anchors.fill: parent
    }
}
