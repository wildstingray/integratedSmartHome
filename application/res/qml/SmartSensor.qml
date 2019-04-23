import QtQuick 2.11
import QtQuick.Controls 2.2
import com.integratedSmartHome 1.0

Rectangle {
    anchors.fill: parent
    color: Style.darkGray
    anchors.margins: 3

    Label {
        anchors.centerIn: parent
        font.pixelSize: 60
        text: payload
    }

    SmartButton {
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent.width/4
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
        width: parent.width/4
        height: width
        visible: parent.hasImage
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
