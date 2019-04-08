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
            Loader {
                id: dynamicLoader
                anchors.fill: parent
                source: qmlUrl
            }
        }
    }

    ListModel {
        id: loaderTypes
        ListElement {
            deviceTypeName: "button"
            qmlUrl: "qrc:/qml/ComplexSmartButton.qml"
        }
        ListElement {
            deviceTypeName: "sensor"
            qmlUrl: "qrc:/qml/SmartSensor.qml"
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
