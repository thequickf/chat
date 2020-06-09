import QtQuick 2.15

Item {
    id: mainItem

    property string text: ""
    property bool own: false

    height: messageText.height + 20
    Item {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: mainItem.own ? undefined : parent.left
            right: mainItem.own ? parent.right : undefined
        }
        anchors.margins: 5
        width: Math.min(messageTextMetrics.tightBoundingRect.width + 14,
                        mainItem.width * 0.9)

        Rectangle {
            anchors.fill: parent
            radius: 5
            color: mainItem.own ? "#d0ebff" : "#f1f3f5"

            Text {
                id: messageText

                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.Wrap
                text: mainItem.text
            }

            TextMetrics {
                id: messageTextMetrics

                font: messageText.font
                text: max_row(messageText.text)

                function max_row(message) {
                    const rows = message.split('\n')
                    var max_size = 0
                    var res = ""
                    for (const row of rows) {
                        if (row.length > max_size) {
                            max_size = row.length
                            res = row
                        }
                    }
                    return res
                }
            }
        }
    }
}
