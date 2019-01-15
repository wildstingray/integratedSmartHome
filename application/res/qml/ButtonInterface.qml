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
            SmartButton {
                property variant win;
                anchors.fill: parent
                anchors.margins: 3
                image: imageSource
                hasImage: imageSource == "qrc:/img/plus.svg" ? false : true
                widthScaler: imageWidthScaler
                heightScaler: imageHeightScaler
                onClicked: {
                    if (isRegistered) {

                    }
                    else {
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
