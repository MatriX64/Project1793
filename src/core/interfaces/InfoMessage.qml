import QtQuick 2.7
import QtQuick.Dialogs 1.2

MessageDialog {
    objectName: "information"
    title: "Information"
    icon: StandardIcon.Information
    modality: Qt.ApplicationModal
    onAccepted: close()

    signal closeSignal()
    onVisibilityChanged: closeSignal()
}
