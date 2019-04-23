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

}
