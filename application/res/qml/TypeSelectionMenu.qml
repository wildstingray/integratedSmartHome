import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Popup {
    property var givenIndex: index
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
                    smartDevicesModel.setData(givenIndex,deviceName,SmartDevicesModel.DeviceName)
                    smartDevicesModel.setData(givenIndex,button.image,SmartDevicesModel.ImageSource)
                    smartDevicesModel.setData(givenIndex,button.widthScaler,SmartDevicesModel.ImageWidthScaler)
                    smartDevicesModel.setData(givenIndex,button.heightScaler,SmartDevicesModel.ImageHeightScaler)
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
