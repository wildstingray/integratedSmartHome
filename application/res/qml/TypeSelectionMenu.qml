import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Rectangle {
    id: popupWindow
    color: Style.darkGray
    property var givenIndex: index

    //Menu information
    property bool isEditing: false

    x: 10
    y: 10
    z: 1
    width: parent.width - 20
    height: parent.height - 20
    Component {
        id: popupDelegate
        Item {
            height: buttonView.cellHeight
            width: buttonView.cellWidth
            SmartButton {
                id: button
                anchors.fill: parent
                anchors.margins: 3
                image: imageSource
                widthScaler: imageWidthScaler
                heightScaler: imageHeightScaler
                labelText: deviceType
                onClicked: {
                    menuLoader.setSource(settingsMenu)
                    menuLoader.visible = true
                    buttonView.visible = false
                }
            }
        }
    }

    ListModel {
        id: listModel
        ListElement {
            deviceType: "Button"
            imageSource: "qrc:/img/lightbulbicon_Black.png"
            imageWidthScaler: 1.6
            imageHeightScaler: 1.35
            settingsMenu: "qrc:/qml/SmartDeviceSettingsMenu.qml"
        }
        ListElement {
            deviceType: "Sensor"
            imageSource: "qrc:/img/tempSensor.png"
            imageWidthScaler: 2
            imageHeightScaler: 1.45
            settingsMenu: "qrc:/qml/SmartSensorSettingsMenu.qml"
            qmlLoaderUrl: "qrc:/qml/SmartSensor.qml"
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
        anchors.fill: parent
    }
}
