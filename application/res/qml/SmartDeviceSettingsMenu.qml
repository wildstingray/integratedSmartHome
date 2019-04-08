import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Item {
    anchors.fill:parent
    property var targetObject: false
    property bool isEditing: editing
    property string defaultTopic
//    property int typeCount: 1

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
        text: isEditing ? smartDevicesModel.data(givenIndex, SmartDevicesModel.TopicString) : defaultTopic + "/" + smartDevicesModel.objectCounter
        width: nameTextField.width
        horizontalAlignment: nameTextField.horizontalAlignment
        font.pixelSize: 24
        color: Style.lightGreen
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 3
        height: 50
        width: 120
        text: "Accept"
        onClicked: {
            smartDevicesModel.incObjectCounter()
            smartDevicesModel.setData(givenIndex,nameTextField.text,SmartDevicesModel.DeviceName)
            smartDevicesModel.setData(givenIndex,topicTextField.text,SmartDevicesModel.TopicString)
            if (!isEditing)
            {
                smartDevicesModel.add()
            }
            if (targetObject)
            {
                targetObject.close()
            }
        }
    }

}
