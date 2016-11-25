import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: root
    WPS_AttackForm {
        anchors.fill: parent
        testButton.onClicked: qmlScream()
    }
}
