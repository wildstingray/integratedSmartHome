import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import "."
import QtGraphicalEffects 1.0

Button {
    id: button
    property bool isOn: false
    property alias image: icon.source
    property bool hasImage: false
    property double widthScaler: 5
    property double heightScaler: 5
    checkable: hasImage

    Image {
        id: icon
        anchors.centerIn: parent
        width: parent.width/button.widthScaler
        height: parent.height/button.heightScaler
        source: "qrc:/img/plus.svg"

        //Might be useful in the future to use QQmlAbstractUrlInterceptor with prerendered versions of an icon
        //for the different theme colors. (example: "+dark")
        //Would allow for different icons besides just a color change to be used
        ColorOverlay {
            visible: parent.parent.hasImage
            anchors.fill: parent
            source: parent
            color: parent.parent.checked ? "white" : "Black"
        }
    }
}
