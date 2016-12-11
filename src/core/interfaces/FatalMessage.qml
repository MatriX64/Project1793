import QtQuick 2.4
import QtQuick.Window 2.0

Window {
    visible: true
    id: root
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    width: 400
    height: 100
    flags: Qt.SplashScreen
    title: "Project1793. Error"

    signal quit_signal()
    FatalMessageForm {
        terminationButton.onClicked: quit_signal()

    }
}
