import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Item {
    id: rgbSettingsItem
    anchors.fill: parent

    property string defaultTopic: "home/leds"

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
        text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.TopicString) : rgbSettingsItem.defaultTopic + "/" + smartDevicesModel.objectCounter
        width: nameTextField.width
        horizontalAlignment: nameTextField.horizontalAlignment
        font.pixelSize: 24
        color: Style.lightGreen
    }

    SettingsMenuButtons {
        property bool successful: true
        onAccepted: function() {
            successful = true
            smartDevicesModel.incObjectCounter()
            successful &= smartDevicesModel.setData(givenIndex,"qrc:/qml/RGBDevice.qml",SmartDevicesModel.QmlUrl)
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
}
