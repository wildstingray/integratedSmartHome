import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import "."
import QtGraphicalEffects 1.0

Button {
    id: button
    property bool isOn: false
    property alias image: icon.source
    property bool hasImage: false
    property double widthScaler: 5
    property double heightScaler: 5
    checkable: true
    Rectangle {
        visible: parent.checked
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 4
        color: Style.accent
    }

    Image {
        id: icon
        anchors.centerIn: parent
        width: parent.width/button.widthScaler
        height: parent.height/button.heightScaler
        source: "qrc:/img/plus.svg"

        ColorOverlay {
            visible: parent.parent.hasImage
            anchors.fill: parent
            source: parent
            color: parent.parent.checked ? "white" : "Black"
        }
    }
//    background: Rectangle {
//        id: backgroundRec
//        color: parent.isOn ? (parent.highlighted ?  Style.lightGray : Style.darkGray) : (parent.highlighted ?  Style.lightGray : Style.gray)
//        radius: width/8
//    }

//    MouseArea {
//        id: buttonArea
//        hoverEnabled: true
//        anchors.fill: parent
//        onClicked: parent.isOn = !parent.isOn
//    }
}
