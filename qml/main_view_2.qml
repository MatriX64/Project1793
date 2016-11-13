import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: "Project1793. Главное окно"
//start_input
    3TabView: {
        0anchors.fill: parent,
        1Tab0: {
            0title: qsTr(\password_attacks\),
            3TabView: {
                0anchors.fill: parent,
                1Tab0: {
                    0title: qsTr(\wep/wpa/wpa2_attacks\),
                    WPS_Attack: {
                        0anchors.fill: parent
                    }
                }
            }
        }
    }
//end_input
    }
        }
    }
//end_input
}