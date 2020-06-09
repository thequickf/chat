import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    ListModel {
        id: roomModel

        property int selected: 0
        ListElement { name: "Global" }
        ListElement { name: "Alice" }
        ListElement { name: "Bob" }
        ListElement { name: "Jane" }
        ListElement { name: "Harry" }
        ListElement { name: "Wendy" }
        ListElement { name: "Michael" }
        ListElement { name: "Tomas" }
        ListElement { name: "John" }
        ListElement { name: "Greg" }
        ListElement { name: "Jesus" }
        ListElement { name: "Albert" }
        ListElement { name: "Forrest" }
        ListElement { name: "Phillip" }
    }

    Flickable {
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: 35 * roomModel.count
        contentWidth: parent.width

        ColumnLayout {
            anchors.fill: parent

            Repeater {
                model: roomModel

                Rectangle {
                    id: roomItem

                    Layout.fillWidth: true
                    Layout.minimumHeight: 30
                    Layout.maximumHeight: 30
                    color: index == roomModel.selected ? "#4dabf7" : "#e9ecef"

                    Text {
                        anchors.centerIn: parent
                        text: name
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: roomModel.selected = index
                    }
                }
            }
        }
    }
}
