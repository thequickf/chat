import QtQuick 2.15
import QtQuick.Window 2.15

import "ChatComponents"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Chat")

    Chat {
        anchors.centerIn: parent
        anchors.fill: parent
    }
}
