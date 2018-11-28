import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Popup {
    Component {
        id: modelDelegate //Add three buttons at a time, have one button at bottom to add 3 more
        Item {
            width: mainItem.width/3
            height: mainItem.height/2
            SmartButton {
                anchors.fill: parent
                anchors.margins: 3
                image: "qrc:/img/lightbulbicon.svg"
                hasImage: true
                widthScaler: Style.lightBulbWidthScaler
                heightScaler: Style.lightBulbHeightScaler
            }
        }
    }

    ListView {
        id: buttonListView
        anchors.fill: parent
        model: smartDevicesModel
        delegate: modelDelegate
        focus: true
    }
}
