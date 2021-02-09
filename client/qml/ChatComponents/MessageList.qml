import QtQuick 2.15

Item {
    id: mainItem

    FindMessageField {
        id: findMessageField

        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }
        height: 0
        visible: false

        onActiveChanged: {
            // the order is important
            if (active) {
                height = implicitHeight
                visible = true
                findMessageButton.enabled = false
                findMessageButton.visible = false
                flickableItem.contentHeight = messagesColumn.height
                messagesColumn.y = 0
            } else {
                findMessageButton.enabled = true
                findMessageButton.visible = true
                messagesColumn.y = findMessageButton.height
                flickableItem.contentHeight += findMessageButton.height
                height = 0
                visible = false
            }

        }
    }

    Rectangle {
        id: findMessageButton
        anchors {
            top: parent.top
            right: parent.right
        }
        border.color: "#bba5d8ff"
        border.width: 2
        color: "#bbdee2e6"
        height: findButtonText.height + 10
        width: findButtonText.width + 10
        z: 1

        Text {
            id: findButtonText
            text: "Find Message"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                findMessageField.active = !findMessageField.active
            }
        }
    }

    Flickable {
        id: flickableItem

        anchors {
            left: parent.left
            top: findMessageField.bottom
            right: parent.right
            bottom: parent.bottom
        }
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        contentHeight: messagesColumn.height  + findMessageButton.height
        contentWidth: mainItem.width

        Connections {
            target: messagesColumn

            function onHeightChanged() {
                if (flickableItem.atYBeginning)
                    console.log("atYBeginning")
                if (flickableItem.atYEnd)
                    console.log("atYEnd")
                var ratio = 1.0 - flickableItem.visibleArea.heightRatio;
                var endPos = flickableItem.contentHeight * ratio;
                flickableItem.contentY = endPos
                console.log(messagesColumn.children[0].y)
                console.log(messagesColumn.children[1].y)
                console.log(messagesColumn.children[2].y)
            }
        }

        Column {
            id: messagesColumn

            width: mainItem.width
            y: findMessageButton.height

            Repeater {
                model: messageListModel

                Message {
                    width: mainItem.width
                    text: message
                    own: mine
                }
            }
        }
    }
}
