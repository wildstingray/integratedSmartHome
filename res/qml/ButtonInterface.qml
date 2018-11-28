import QtQuick 2.11
import QtQuick.Controls 2.2
import "."

Item {
    id: mainItem
    anchors.fill: parent
    property int margins: 8

    Component {
        id: modelDelegate //Add three buttons at a time, have one button at bottom to add 3 more
        Item {
            width: mainItem.width/3
            height: mainItem.height/2
            SmartButton {
                anchors.fill: parent
                anchors.margins: 3
                image: "qrc:/img/lightbulbicon.svg"
                hasImage: true
                widthScaler: Style.lightBulbWidthScaler
                heightScaler: Style.lightBulbHeightScaler
            }
        }
    }

    ListView {
        id: buttonListView
        anchors.fill: parent
        model: smartDevicesModel
        delegate: modelDelegate
        focus: true

    }

    /*
    SmartButton {
        id: leftTopButton
        anchors.top: parent.top
        anchors.bottom: middleTopButton.bottom
        anchors.left: parent.left
        anchors.right: middleTopButton.left
        anchors.rightMargin: parent.margins
    }

    SmartButton {
        id: middleTopButton
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/3
        height: (parent.height/2)-parent.margins
        anchors.top: parent.top
        image: "qrc:/img/lightbulbicon.svg"
        hasImage: true
        widthScaler: Style.lightBulbWidthScaler
        heightScaler: Style.lightBulbHeightScaler
    }

    SmartButton {
        id: rightTopButton
        anchors.top: parent.top
        anchors.bottom: middleTopButton.bottom
        anchors.right: parent.right
        anchors.left: middleTopButton.right
        anchors.leftMargin: parent.margins
        image: "qrc:/img/lightbulbicon.svg"
        hasImage: true
        widthScaler: Style.lightBulbWidthScaler
        heightScaler: Style.lightBulbHeightScaler
    }

    SmartButton {
        id: leftBottomButton
        anchors.top: middleTopButton.bottom
        anchors.topMargin: parent.margins
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: middleTopButton.left
        anchors.rightMargin: parent.margins
    }

    SmartButton {
        id: middleBottomButton
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/3
        anchors.bottom: parent.bottom
        anchors.top: middleTopButton.bottom
        anchors.topMargin: parent.margins
    }

    SmartButton {
        id: rightBottomButton
        anchors.top: middleTopButton.bottom
        anchors.topMargin: parent.margins
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: middleTopButton.right
        anchors.leftMargin: parent.margins
    }
    */
}
