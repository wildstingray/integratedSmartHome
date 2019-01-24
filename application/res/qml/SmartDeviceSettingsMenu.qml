import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Item {
    anchors.fill:parent
    property var targetObject: false
    property bool isEditing: editing

    Item {
        id: nameItem
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 3
        width: nameLabel.width + nameTextField.width
        height: nameTextField.height
        Label {
            id: nameLabel
            anchors.top: parent.top
            height: 50
            text: "Device Name:"
            font.pointSize: 20
        }
        TextField {
            id: nameTextField
            anchors.left: nameLabel.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5
            width: 140
        }
    }

    Item {
        id: ssidItem
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: nameItem.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 3
        width: ssidLabel.width + ssidTextField.width
        height: ssidTextField.height
        Label {
            id: ssidLabel
            anchors.top: parent.top
            height: 50
            text: "SSID:"
            font.pointSize: 20
        }
        TextField {
            id: ssidTextField
            anchors.left: ssidLabel.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5
            width: 140
        }
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 3
        height: 50
        width: 120
        text: "Accept"
        onClicked: {
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
