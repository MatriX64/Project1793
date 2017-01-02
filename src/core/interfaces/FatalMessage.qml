import QtQuick 2.7
import QtQuick.Dialogs 1.2

MessageDialog {
    objectName: "error"
    title: "Critical error"
    icon: StandardIcon.Critical
    modality: Qt.ApplicationModal
    onAccepted: close()

    signal closeSignal()
    onVisibilityChanged: {
        closeSignal()
        Qt.quit()
    }
}
