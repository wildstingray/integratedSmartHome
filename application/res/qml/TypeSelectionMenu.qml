import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Rectangle {
    id: popupWindow
    color: Style.darkGray
    property var givenIndex: index
    property string selectedDefualtTopic
    property string deviceSettingsMenu: "qrc:/qml/SmartDeviceSettingsMenu.qml"
    //    property int typeCounter: 1
    x: 10
    y: 10
    z: 1
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
                labelText: deviceType
                property bool successful: true
                onClicked: {
                    popupWindow.selectedDefualtTopic = defaultTopic
                    successful = true
                    successful &= smartDevicesModel.setData(givenIndex,button.image,SmartDevicesModel.ImageSource)
                    successful &= smartDevicesModel.setData(givenIndex,button.widthScaler,SmartDevicesModel.ImageWidthScaler)
                    successful &= smartDevicesModel.setData(givenIndex,button.heightScaler,SmartDevicesModel.ImageHeightScaler)
                    if (successful)
                    {
                        popupWindow.deviceSettingsMenu = settingsMenu
                        menuLoader.visible = true
                        buttonView.visible = false
                    }
                    else
                    {
                        smartDevicesModel.resetAtIndex(givenIndex)
                        //TODO throw warning to user on failure
                    }


                    //popupWindow.close()
                }
            }
        }
    }

    ListModel {
        id: loaderTypes
        ListElement {
            deviceTypeName: "button"
            qmlUrl: "qrc:/qml/ComplexSmartButton.qml"
        }
        ListElement {
            deviceTypeName: "sensor"
            qmlUrl: "qrc:/qml/SmartSensor.qml"
        }
    }

    ListModel {
        id: listModel
        ListElement {
            deviceType: "SmartBulb"
            imageSource: "qrc:/img/lightbulbicon_Black.png"
            imageWidthScaler: 1.6
            imageHeightScaler: 1.35
            defaultTopic: "/home/lights"
            settingsMenu: "qrc:/qml/SmartDeviceSettingsMenu.qml"
            //property int typeCount: 1
        }
        ListElement {
            deviceType: "Other"
            imageSource: "qrc:/img/Wireless-icon.png"
            imageWidthScaler: 2
            imageHeightScaler: 2
            defaultTopic: "/home/relay"
            settingsMenu: "qrc:/qml/SmartDeviceSettingsMenu.qml"
            //property int typeCount: 1
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

    Loader {
        id: menuLoader
        visible: false
        z: 2
        source: popupWindow.deviceSettingsMenu
    }

    SmartDeviceSettingsMenu {
        visible: !buttonView.visible
        targetObject: popupWindow
        isEditing: editing
        defaultTopic: popupWindow.selectedDefualtTopic
        //        typeCount: popupWindow.typeCounter
    }
}
