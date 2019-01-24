import QtQuick 2.11
import QtQuick.Controls 2.2
import "."

Item {
    id: mainItem
    anchors.fill: parent
    property int margins: 8

    Component {
        id: modelDelegate //Add three buttons at a time, have one button at bottom to add 3 more
        Item {
            width: mainItem.width/3
            height: mainItem.height/2
            property bool editing: false
            property variant win;
            SmartButton {
                anchors.fill: parent
                anchors.margins: 3
                image: imageSource
                hasImage: imageSource != "qrc:/img/plus.svg"
                widthScaler: imageWidthScaler
                heightScaler: imageHeightScaler
                checkable: hasImage
                onClicked: {
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
                    image: "qrc:/img/trash.svg"
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
                    image: "qrc:/img/pencil.svg"
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
