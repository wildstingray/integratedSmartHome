import QtQuick 2.11
import QtQuick.Controls 2.2
import "."
import com.integratedSmartHome 1.0

Item {
    id: mainItem
    anchors.fill: parent
    property int margins: 0
    property var raspiClient

    Component {
        id: modelDelegate
        Item {
            width: mainItem.width/3
            height: mainItem.height/2
            property bool editing: false
            property variant win;
            SmartButton {
                anchors.fill: parent
                anchors.margins: 3
                image: imageSource
                hasImage: imageSource != "qrc:/img/plus.png"
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

                    }
                    else {
                        var component = Qt.createComponent("TypeSelectionMenu.qml");
                        win = component.createObject(mainItem);
                        win.open();
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
        }
    }

    GridView {
        id: buttonListView
        anchors.fill: parent
        model: smartDevicesModel
        delegate: modelDelegate
        focus: true
        cellWidth: mainItem.width/3
        cellHeight: mainItem.height/2
    }
}
