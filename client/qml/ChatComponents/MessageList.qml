import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: mainItem

    ListModel {
        id: messageModel

        ListElement {
            my: true
            message: "Hey you, out there in the cold\
 Getting lonely, getting old\
 Can you feel me?\
 Hey you, standing in the aisles\
 With itchy feet and fading smiles\
 Can you feel me?\
 Hey you, don't help them to bury the light\
 Don't give in without a fight"
        }
        ListElement {
            my: true
            message: "Hey you, out there in the cold\n\
Getting lonely, getting old\n\
Can you feel me?\n\
Hey you, standing in the aisles\n\
With itchy feet and fading smiles\n\
Can you feel me?\n\
Hey you, don't help them to bury the light\n\
Don't give in without a fight"
        }
        ListElement {
            my: false
            message: "Who was born in a house full of pain.\
 Who was trained not to spit in the fan.\
 Who was told what to do by the man.\
 Who was broken by trained personnel.\
 Who was fitted with collar and chain.\
 Who was given a pat on the back.\
 Who was breaking away from the pack.\
 Who was only a stranger at home.\
 Who was ground down in the end.\
 Who was found dead on the phone.\
 Who was dragged down by the stone.\
 Who was dragged down by the stone."
        }
        ListElement {
            my: true
            message: "Who was told what to do by the man."
        }
        ListElement {
            my: false
            message: "Waters\nRoger\nSyd\nBarret\nTest?"
        }
        ListElement {
            my: true
            message: "Harry\nPotter"
        }
        ListElement {
            my: false
            message: "First"
        }
        ListElement {
            my: true
            message: "Second"
        }
        ListElement {
            my: true
            message: "Third"
        }
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        Column {
            anchors.fill: parent

            Repeater {
                model: messageModel

                Message {
                    width: mainItem.width
                    text: message
                    own: my
                }
            }
        }
    }
}
