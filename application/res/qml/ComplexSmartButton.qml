import QtQuick 2.11
import QtQuick.Controls 2.2
import com.integratedSmartHome 1.0

SmartButton {
    anchors.fill: parent
    anchors.margins: 3
    property int givenIndex: index
    image: imageSource
    hasImage: image != "qrc:/img/plus.png"
    widthScaler: imageWidthScaler
    heightScaler: imageHeightScaler
    checkable: hasImage
    labelText: hasImage ? name : ""
    onClicked: {
        if (raspiClient.state === MqttClient.Disconnected)
        {
            raspiClient.connectToHost()
            console.log("Client Connecting...")
        }

        if (hasImage) {
            var value = checked ? 0x01 : 0x00
            raspiClient.publish(topicName, value)
            console.log("Sent Topic: " + topicName + " with payload: " + value)

        }
        else {
            var component = Qt.createComponent("TypeSelectionMenu.qml");
            win = component.createObject(mainItem);
//            win.open();
        }
    }

    SmartButton {
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent/16
        height: width
        visible: parent.hasImage
        image: "qrc:/img/trash.png"
        widthScaler: 2
        heightScaler: 2
        onClicked: {
            smartDevicesModel.resetAtIndex(index)
        }
    }

    SmartButton {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent/16
        height: width
        visible: parent.hasImage
        image: "qrc:/img/pencil.png"
        widthScaler: 2
        heightScaler: 2
        onClicked: {
            editing = true
            var component = Qt.createComponent("TypeSelectionMenu.qml");
            win = component.createObject(mainItem);
            win.open();
        }
    }
}
