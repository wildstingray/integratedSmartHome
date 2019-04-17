import QtQuick 2.2
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.1
import "./colorWheelInformation"
import "colorWheelInformation/ColorUtils.js" as ColorUtils

Rectangle {
    Material.elevation: 2
    id: root
    signal disableInteractive
    signal enableInteractive
    anchors.fill: parent
    focus: true
    color: Style.darkGray

    // Color value in RGBA with floating point values between 0.0 and 1.0.

    property vector4d colorHSVA: Qt.vector4d(1, 0, 1, 1)
    QtObject {
        id: m
        // Color value in HSVA with floating point values between 0.0 and 1.0.
        property vector4d colorRGBA: ColorUtils.hsva2rgba(root.colorHSVA)
    }

    signal accepted

    onAccepted: {
        //        console.debug(colorHSVA)
        //        console.debug(m.colorRGBA)
    }

    Wheel {
        id: wheel
        height: parent.height/1.3
        width: parent.width/1.3
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 3

        hue: colorHSVA.x
        saturation: colorHSVA.y
        onUpdateHS: {
            colorHSVA = Qt.vector4d(hueSignal,saturationSignal, colorHSVA.z, colorHSVA.w)
        }
        onAccepted: {
            root.accepted()
        }
        onEnableMovement: root.enableInteractive()
        onDisableMovement: root.disableInteractive()
    }

    Item {
        id: sliderLocation
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: wheel.bottom
    }

    // brightness picker slider
    Item {
        id: brightnessSlider
        anchors.horizontalCenter: sliderLocation.horizontalCenter
        anchors.verticalCenter: sliderLocation.verticalCenter
        rotation: 90

        height: parent.height
        width: parent.height/10

        //Brightness background
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop {
                    id: brightnessBeginColor
                    position: 0.0
                    color: {
                        var rgba = ColorUtils.hsva2rgba(
                                    Qt.vector4d(colorHSVA.x,
                                                colorHSVA.y, 1, 1))
                        return Qt.rgba(rgba.x, rgba.y, rgba.z, rgba.w)
                    }
                }
                GradientStop {
                    position: 1.0
                    color: "#000000"
                }
            }
        }

        VerticalSlider {
            id: brigthnessSlider
            anchors.fill: parent
            value: colorHSVA.z
            onValueChanged: {
                colorHSVA = Qt.vector4d(colorHSVA.x, colorHSVA.y, value, colorHSVA.w)
            }
            onAccepted: {
                root.accepted()
            }
        }
    }

    // text inputs
    Column {
        anchors.top: parent.top
        anchors.bottom: sliderLocation.top
        anchors.right: sliderLocation.right
        anchors.topMargin: 3
        anchors.rightMargin: 3
        width: 70
        spacing: 10

        // current color display
        Rectangle {
            id: outputColorRect
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height/3
            CheckerBoard {
                cellSide: 5
            }
            Rectangle {
                id: colorDisplay
                width: parent.width
                height: parent.height
                border.width: 1
                border.color: "black"
                color: Qt.rgba(m.colorRGBA.x, m.colorRGBA.y, m.colorRGBA.z)
                opacity: m.colorRGBA.w
            }
        }


        // current color value
        Item {
            id: outputColor
            height: parent.height/4
            anchors.left: outputColorRect.left
            anchors.right: outputColorRect.right

            Text {
                id: captionBox
                text: "#"
                width: 18
                height: parent.height
                color: "#AAAAAA"
                font.pixelSize: 16
                font.bold: true
            }
            PanelBorder {
                height: parent.height
                anchors.left : captionBox.right
                width: parent.width - captionBox.width
                TextInput {
                    id: currentColor
                    color: "#AAAAAA"
                    selectionColor: "#FF7777AA"
                    font.pixelSize: 12
                    font.capitalization: "AllUppercase"
                    maximumLength: 9
                    focus: true
                    text: ColorUtils.hexaFromRGBA(m.colorRGBA.x, m.colorRGBA.y,
                                                  m.colorRGBA.z, m.colorRGBA.w)
                    font.family: "TlwgTypewriter"
                    selectByMouse: true
                    validator: RegExpValidator {
                        regExp: /^([A-Fa-f0-9]{6})$/
                    }
                    onEditingFinished: {
                        var colorTmp = Qt.vector4d( parseInt(text.substr(0, 2), 16) / 255,
                                                   parseInt(text.substr(2, 2), 16) / 255,
                                                   parseInt(text.substr(4, 2), 16) / 255,
                                                   colorHSVA.w) ;
                        colorHSVA = ColorUtils.rgba2hsva(colorTmp)
                    }
                }
            }
        }

        // R, G, B color values boxes
        Column {
            id: rgbColumn
            anchors.left: outputColor.left
            anchors.right: outputColor.right

            NumberBox {
                id: red
                caption: "R"
                value: Math.round(m.colorRGBA.x * 255)
                min: 0
                max: 255
                decimals: 0
                onAccepted: {
                    var colorTmp = Qt.vector4d( boxValue / 255,
                                               m.colorRGBA.y,
                                               m.colorRGBA.z,
                                               colorHSVA.w) ;
                    colorHSVA = ColorUtils.rgba2hsva(colorTmp)
                    root.accepted()
                }
            }
            NumberBox {
                id: green
                caption: "G"
                value: Math.round(m.colorRGBA.y * 255)
                min: 0
                max: 255
                decimals: 0
                onAccepted: {
                    var colorTmp = Qt.vector4d( m.colorRGBA.x,
                                               boxValue / 255,
                                               m.colorRGBA.z,
                                               colorHSVA.w) ;
                    colorHSVA = ColorUtils.rgba2hsva(colorTmp)
                    root.accepted()
                }
            }
            NumberBox {
                id: blue
                caption: "B"
                value: Math.round(m.colorRGBA.z * 255)
                min: 0
                max: 255
                decimals: 0
                onAccepted: {
                    var colorTmp = Qt.vector4d( m.colorRGBA.x,
                                               m.colorRGBA.y,
                                               boxValue / 255,
                                               colorHSVA.w) ;
                    colorHSVA = ColorUtils.rgba2hsva(colorTmp)
                    root.accepted()
                }
            }
        }
    }
}
