import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.integratedSmartHome 1.0

Popup {
    property var givenIndex: index
    property bool isEditing: editing
    id: popupWindow
    x: 10
    y: 10
    width: parent.width - 20
    height: parent.height - 20
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
                property bool successful: true
                onClicked: {
                    successful = true;
                    successful &= smartDevicesModel.setData(givenIndex,deviceName,SmartDevicesModel.DeviceName)
                    successful &= smartDevicesModel.setData(givenIndex,button.image,SmartDevicesModel.ImageSource)
                    successful &= smartDevicesModel.setData(givenIndex,button.widthScaler,SmartDevicesModel.ImageWidthScaler)
                    successful &= smartDevicesModel.setData(givenIndex,button.heightScaler,SmartDevicesModel.ImageHeightScaler)
                    if (successful)
                    {
                        if (!isEditing) {
                            smartDevicesModel.add()
                        }
                    }
                    else
                    {
                        smartDevicesModel.resetAtIndex(givenIndex)
                        //TODO throw warning to user on failure
                    }


                    popupWindow.close()
                }
            }
        }
    }

    ListModel {
        id: listModel
        ListElement {
            deviceName: "SmartBulb"
            imageSource: "qrc:/img/lightbulbicon.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
        ListElement {
            imageSource: "qrc:/img/wifi.svg"
            imageWidthScaler: 1.4
            imageHeightScaler: 1.2
        }
    }

    GridView {
        id: buttonView
        anchors.fill: parent
        model: listModel
        delegate: popupDelegate
        focus: true
        cellWidth: popupWindow.width/3 - 10
        cellHeight: popupWindow.height/2
        clip: true
    }
}
