import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Popup {
    id: popupWindow
    x: 10
    y: 10
    width: parent.width - 20
    height: parent.height - 20
    Component {
        id: popupDelegate
        Item {
            width: popupWindow.width/3 - 10
            height: popupWindow.height/2
            SmartButton {
                id: button
                anchors.fill: parent
                anchors.margins: 3
                image: imageSource
                widthScaler: imageWidthScaler
                heightScaler: imageHeightScaler
                onClicked: {
                    smartDevicesModel.setData(0,deviceName,smartDevicesModel.DeviceName)
                    smartDevicesModel.setData(0,button.image,smartDevicesModel.ImageSource)
                    smartDevicesModel.setData(0,button.widthScaler,smartDevicesModel.ImageWidthScaler)
                    smartDevicesModel.setData(0,button.heightScaler,smartDevicesModel.ImageHeightScaler)
                    popupWindow.close()
                }
            }
        }
    }

    ListModel {
        id: listModel
        ListElement {
            deviceName: "SmartBulb"
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
    }

    GridView {
        id: buttonView
        anchors.fill: parent
        model: listModel
        delegate: popupDelegate
        focus: true
        cellWidth: popupWindow.width/3 - 10
        cellHeight: popupWindow.height/2
        clip: true
    }
}
