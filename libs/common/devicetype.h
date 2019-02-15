#ifndef DEVICETYPE_H
#define DEVICETYPE_H

#include <QObject>
#include <QString>

class DeviceType
{
public:
    DeviceType(/*QString deviceTypeName = "Add",*/ QString imageSource = "qrc:/img/plus.png", double imageWidthScalar = 4.0, double imageHeightScaler = 4.0);
//    static const DeviceType SmartBulb;

    QString getImageSource();
    double getImageWidthScaler();
    double getImageHeightScaler();
//    QString getDeviceTypeName();

    void setImageSource(QString newSource);
    void setImageWidthScaler(double newScaler);
    void setImageHeightScaler(double newScaler);
//    void setDeviceTypeName(QString newName);

    bool operator!=(const DeviceType &a);

private:
//    QString m_deviceTypeName;
    QString m_imageSource;
    double m_imageWidthScaler;
    double m_imageHeightScaler;
};

//TODO
//const DeviceType DeviceType::SmartBulb = DeviceType("SmartBulb", "qrc:/img/lightbulbicon.svg", 1.4, 1.2);

Q_DECLARE_METATYPE(DeviceType)


#endif // DEVICETYPE_H
