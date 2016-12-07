/*
 * Copyright (c) 2016, MatriXSan <matrix3sai@gmail.com>
 *
 *  This file is part of Project1793.
 *
 *  Project1793 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project1793 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Project1793.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    id: root
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    width: 500
    height: 100
    flags: Qt.SplashScreen
    title: "Project1793. Ошибка"

    Text {
        text: qsTr("Фатальная ошибка. Смотрите лог файл")
        font.family: "Helvetica"
        font.pointSize: 17
        color: "black"
    }

    signal quit_signal()
    Button {
        anchors.centerIn: parent
        text: qsTr("Ok")
        onClicked: root.quit_signal()
    }
}
