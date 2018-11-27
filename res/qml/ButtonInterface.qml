import QtQuick 2.11
import QtQuick.Controls 2.2
import "."

Item {
    anchors.fill: parent
    property int margins: 8
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
}
