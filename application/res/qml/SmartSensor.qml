import QtQuick 2.11
import QtQuick.Controls 2.2
import com.integratedSmartHome 1.0

Rectangle {
    anchors.fill: parent
    color: Style.darkGray
    anchors.margins: 3

    property string humidity: ""
    property string celsius: ""
    property string fahrenheit: ""
    property string fullStr: payload
    property int viewIndex: 0

    MouseArea {
        anchors.fill: parent
        onClicked: {
            viewIndex = (viewIndex + 1) % 3

            switch (viewIndex)
            {
            case 0:
                sensor.text = humidity
                break;
            case 1:
                sensor.text = celsius
                break;
            case 2:
                sensor.text = fahrenheit
                break;
            default:
                break;
            }
        }
    }

    Label {
        id: sensor
        anchors.centerIn: parent
        font.pixelSize: 60
    }

    onFullStrChanged: {
        humidity = fullStr.substring(0,4)
        humidity = humidity + "%"
        celsius = fullStr.substring(5,9)
        celsius = celsius + "°C"
        fahrenheit = fullStr.substring(10,14)
        fahrenheit = fahrenheit + "°F"

        switch (viewIndex)
        {
        case 0:
            sensor.text = humidity
            break;
        case 1:
            sensor.text = celsius
            break;
        case 2:
            sensor.text = fahrenheit
            break;
        default:
            break;
        }
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
