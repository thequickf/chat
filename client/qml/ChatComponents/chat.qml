import QtQuick 2.15

Item {
    RoomList {
        id: roomList
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: Math.max(parent.width * 0.15, 80)
    }

    MessageList {
        anchors {
            left: roomList.right
            leftMargin: 5
            top: parent.top
            right: parent.right
            bottom: messageTextField.top
        }
    }

    MessageTextField {
        id: messageTextField
        anchors {
            left: roomList.right
            leftMargin: 5
            right: parent.right
            bottom: parent.bottom
        }
    }
}
