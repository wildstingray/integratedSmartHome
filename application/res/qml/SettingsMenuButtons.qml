import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
    anchors.fill: parent
    property alias onAccepted: acceptButton.acceptedFunction
    property alias onCanceled: cancelbutton.canceledFunction
    property bool isEnabled: true

    Button {
        id: acceptButton
        enabled: parent.isEnabled
        anchors.bottom: parent.bottom
        anchors.right: parent.horizontalCenter
        anchors.margins: 3
        height: 50
        width: 120
        text: "Accept"
        property var acceptedFunction: function () {console.log("Unassigned Function, fix me dumb dumb")}
        onClicked: acceptedFunction()
    }

    Button {
        id: cancelbutton
        enabled: parent.isEnabled
        anchors.bottom: acceptButton.bottom
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 3
        height: acceptButton.height
        width: acceptButton.width
        text: "Cancel"
        property var canceledFunction: function() {popupWindow.visible = false;}
        onClicked: canceledFunction()
    }
}
