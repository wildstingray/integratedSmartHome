import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls 2.2
//import "."
//import QtQuick.VirtualKeyboard 2.3
import com.integratedSmartHome 1.0

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

        MqttClient {
            id: raspiClientObj
            hostname: "localhost"
            portNum: 1883
        }

        Rectangle {
            anchors.fill: parent
            color: Style.darkDarkGray

            Item {
                id: buttonInterfaceItem
                anchors.fill: parent
                anchors.topMargin: 20
                anchors.bottomMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                ButtonInterface {
                    raspiClient: raspiClientObj

                }
            }
        }
    }

//TODO keyboard
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
