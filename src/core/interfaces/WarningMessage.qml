import QtQuick 2.7
import QtQuick.Dialogs 1.2

MessageDialog {
    objectName: "warning"
    title: "Warning"
    icon: StandardIcon.Warning
    modality: Qt.ApplicationModal
    onAccepted: close()

    signal closeSignal()
    onVisibilityChanged: closeSignal()
}
