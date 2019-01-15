import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls.Universal 2.3
//import QtQuick.VirtualKeyboard 2.3

Window {
    id: window
    visible: true
    width: 800
    height: 480
    title: qsTr("Integrated Smart Home")
    color: "black"

    Item {
        id: mainItem
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "#232323"

            Item {
                anchors.fill: parent
                anchors.topMargin: 30
                anchors.bottomMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                ButtonInterface {

                }
            }
        }
    }

//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}
