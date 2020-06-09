import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property string text: textArea.text

    height: mainItem.height + 4
    color: "#74c0fc"

    ScrollView {
        id: mainItem

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 2
        }
        clip: true
        height: Math.min(contentHeight, 60)
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        TextArea {
            id: textArea

            wrapMode: TextEdit.Wrap
            placeholderText: qsTr("Message")
            rightPadding: 40
            background: Rectangle {
                color: "white"
            }
        }
    }

    Item {
        anchors {
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
        visible: textArea.text != ""
        width: 40

        Text {
            anchors.centerIn: parent
            text: "Send"
            color: "#74c0fc"
            font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                // TODO
                textArea.text = ""
            }
        }
    }
}
