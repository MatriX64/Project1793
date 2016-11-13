import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    width: 900
    height: 700
    title: qsTr("Project1793. Главное окно")
//start_input
    TabView {
        anchors.fill: parent
        Tab {
            title: qsTr("password_attacks")
            TabView {
                anchors.fill: parent
                Tab {
                    title: qsTr("wep/wpa/wpa2_attacks")
                    TabView {
                        anchors.fill: parent
                        Tab {
                            title: qsTr("wps_attack")
                            TabView {
                                anchors.fill: parent
                                Tab {
                                    title: qsTr("eva")
                                    WPS_Attack {
                                        anchors.fill: parent
                                    }
                                }
                            }
                        }
                    }
                }
                Tab {
                    title: qsTr("wps_attack")
                    TabView {
                        anchors.fill: parent
                        Tab {
                            title: qsTr("wep/wpa/wpa2_attacks")
                            TabView {
                                anchors.fill: parent
                                Tab {
                                    title: qsTr("eva")
                                    WPS_Attack {
                                        anchors.fill: parent
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Tab {
            title: qsTr("crypt_test")
            WPS_Attack {
                anchors.fill: parent
            }
        }
    }
//end_input
}
