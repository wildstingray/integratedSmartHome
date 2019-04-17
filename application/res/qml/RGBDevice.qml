import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

ColorWheel {
    anchors.fill: parent
    anchors.margins: 3
//    anchors.fill: parent
//    color: "blue"
    onDisableInteractive: buttonListView.interactive = false
    onEnableInteractive: buttonListView.interactive = true

    onOutputRGBValueChanged: {
        if (raspiClient.state === MqttClient.Disconnected)
        {
            raspiClient.connectToHost()
            console.log("Client Connecting...")
        }

        raspiClient.publish(topicName, '#' + outputRGBValue)
        console.log("Sent Topic: " + topicName + " with payload: " + outputRGBValue)
    }


    SmartButton {
        id: trashButton
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent.width/6
        height: width
        visible: true
        image: "qrc:/img/trash.png"
        widthScaler: 2
        heightScaler: 2
        onClicked: {
            smartDevicesModel.resetAtIndex(index)
        }
    }

    SmartButton {
        id: editButton
        anchors.top: parent.top
        anchors.right: trashButton.left
        anchors.rightMargin: 2
        width: trashButton.width
        height: trashButton.width
        visible: trashButton.visible
        image: "qrc:/img/pencil.png"
        widthScaler: 2
        heightScaler: 2
        onClicked: {
            editing = true
            var component = Qt.createComponent("TypeSelectionMenu.qml");
            win = component.createObject(mainItem);
        }
    }
}
