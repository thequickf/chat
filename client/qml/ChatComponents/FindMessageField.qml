import QtQuick 2.15

Rectangle {
    id: mainItem

    property alias text: textInput.text
    property bool active: false

    border.color: "#bba5d8ff"
    border.width: 2
    color: "white"
    implicitHeight: textInput.height + 10

    Item {
        id: cancelButton

        anchors {
            left: parent.left
            top: parent.top
        }
        height: mainItem.height
        width: height

        Text {
            text: "X"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                active = !active
            }
        }
    }

    TextInput {
        id:textInput

        anchors {
            left: cancelButton.right
            right: navigationArea.left
            leftMargin: 5
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: navigationArea

        anchors {
            right: parent.right
            top: parent.top
        }
        height: mainItem.height
        width: height * 2
    }
}
