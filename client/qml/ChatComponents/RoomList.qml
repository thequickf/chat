import QtQuick 2.15

Item {
    id: mainItem

    Flickable {
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: mainColumn.height
        contentWidth: parent.width

        Column {
            id: mainColumn

            width: mainItem.width
            spacing: 5

            Repeater {
                model: roomListModel

                Rectangle {
                    id: roomItem

                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    color: index == roomListModel.selected_room ? "#4dabf7" : "#e9ecef"
                    height: 30
                    width: mainItem.width

                    Text {
                        anchors.centerIn: parent
                        text: name
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: roomListModel.selected_room = index
                    }
                }
            }
        }
    }
}
