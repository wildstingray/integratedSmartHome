import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Item {
    id: sensorSettingsItem

    property string defaultTopic: "raspi/sensors"

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
        text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.DeviceName) : "Sensor " + smartDevicesModel.objectCounter
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
        text: "Subscribe:"
        font.pointSize: 20
    }
    TextField {
        id: topicTextField
        anchors.left: nameTextField.left
        anchors.verticalCenter: ssidItem.verticalCenter
        anchors.leftMargin: 5
        text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.TopicString) : sensorSettingsItem.defaultTopic + "/" + smartDevicesModel.objectCounter
        width: nameTextField.width
        horizontalAlignment: nameTextField.horizontalAlignment
        font.pixelSize: 24
        color: Style.lightGreen
    }

    SettingsMenuButtons{
        property bool successful: true
        onAccepted: function() {
            successful = true
            smartDevicesModel.incObjectCounter()
            successful &= smartDevicesModel.setData(givenIndex,"qrc:/qml/SmartSensor.qml",SmartDevicesModel.QmlUrl)
            successful &= smartDevicesModel.setData(givenIndex,nameTextField.text,SmartDevicesModel.DeviceName)
            successful &= smartDevicesModel.setData(givenIndex,topicTextField.text,SmartDevicesModel.TopicString)
            if (!successful)
            {
                smartDevicesModel.resetAtIndex(givenIndex)
                console.log("ERROR: Cannot set model values")

            }
            else {
                if (!isEditing)
                {
                    smartDevicesModel.add()
                }
                raspiClient.subscribe(topicTextField.text)
            }

            popupWindow.visible = false;
        }
    }
}
