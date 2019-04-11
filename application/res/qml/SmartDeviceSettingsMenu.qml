import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Item {
    id: settingsItem
    anchors.fill: parent
    property string imageSource: ""
    property double imageWidthScaler: 0
    property double imageHeightScaler: 0
    property string qmlLoaderUrl: "qrc:/qml/ComplexSmartButton.qml"
    property string defaultTopicGiven: "/home/default"


    Label {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 14
        text: pictureSelection.visible ? "Select Picture" : "Change Settings"
    }

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
                    settingsItem.imageSource = model.imageSource
                    settingsItem.imageWidthScaler = model.imageWidthScaler
                    settingsItem.imageHeightScaler = model.imageHeightScaler
                    settingsItem.defaultTopicGiven = model.defaultTopic
                    pictureSelection.visible = false
                }
            }
        }
    }

    ListModel {
        id: buttonModel
        ListElement {
            imageSource: "qrc:/img/lightbulbicon_Black.png"
            imageWidthScaler: 1.6
            imageHeightScaler: 1.35
            defaultTopic: "home/lights"
        }
        ListElement {
            imageSource: "qrc:/img/Wireless-icon.png"
            imageWidthScaler: 2
            imageHeightScaler: 2
            defaultTopic: "home/relay"
        }
    }

    GridView {
        id: pictureSelection
        visible: true
        anchors.fill: parent
        anchors.topMargin: 40
        model: buttonModel
        delegate: popupDelegate
        focus: true
        cellWidth: settingsItem.width/3 - 10
        cellHeight: settingsItem.height/2
        clip: true
    }

    Item {
        id: secondMenuItem
        anchors.fill: parent
        anchors.topMargin: 40
        visible: !pictureSelection.visible

        Label {
            id: nameItem
            x: 50
            y: 30
            height: nameTextField.height
            text: "Device Name:"
            font.pointSize: 20
        }
        TextField {
            id: nameTextField
            x: 320
            anchors.verticalCenter: nameItem.verticalCenter
            anchors.leftMargin: 5
            height: 50
            width: 300
            text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.DeviceName) : "Object " + smartDevicesModel.objectCounter
            font.pixelSize: 24
            color: Style.lightGreen
            horizontalAlignment: TextInput.AlignHCenter
        }


        Label {
            id: ssidItem
            anchors.left: nameItem.left
            anchors.top: nameItem.bottom
            anchors.topMargin: 10
            height: topicTextField.height
            text: "Topic:"
            font.pointSize: 20
        }
        TextField {
            id: topicTextField
            anchors.left: nameTextField.left
            anchors.verticalCenter: ssidItem.verticalCenter
            anchors.leftMargin: 5
            text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.TopicString) : settingsItem.defaultTopicGiven + "/" + smartDevicesModel.objectCounter
            width: nameTextField.width
            horizontalAlignment: nameTextField.horizontalAlignment
            font.pixelSize: 24
            color: Style.lightGreen
        }

        Button {
            enabled: !pictureSelection.visible
            id: acceptButton
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter
            anchors.margins: 3
            height: 50
            width: 120
            text: "Accept"
            property bool successful: true
            onClicked: {
                successful = true
                smartDevicesModel.incObjectCounter()
                successful &= smartDevicesModel.setData(givenIndex,settingsItem.imageSource,SmartDevicesModel.ImageSource)
                successful &= smartDevicesModel.setData(givenIndex,settingsItem.imageWidthScaler,SmartDevicesModel.ImageWidthScaler)
                successful &= smartDevicesModel.setData(givenIndex,settingsItem.imageHeightScaler,SmartDevicesModel.ImageHeightScaler)
                successful &= smartDevicesModel.setData(givenIndex,settingsItem.qmlLoaderUrl,SmartDevicesModel.QmlUrl)
                successful &= smartDevicesModel.setData(givenIndex,nameTextField.text,SmartDevicesModel.DeviceName)
                successful &= smartDevicesModel.setData(givenIndex,topicTextField.text,SmartDevicesModel.TopicString)
                if (!successful)
                {
                    smartDevicesModel.resetAtIndex(givenIndex)
                    console.log("ERROR: Cannot set model values")

                }
                else if (!isEditing)
                {
                    smartDevicesModel.add()
                }

                popupWindow.visible = false;
            }
        }

        Button {
            anchors.bottom: acceptButton.bottom
            anchors.left: parent.horizontalCenter
            anchors.margins: 3
            height: acceptButton.height
            width: acceptButton.width
            text: "Cancel"
            onClicked: {
                popupWindow.visible = false;
            }
        }
    }
}
