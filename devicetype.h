#ifndef DEVICETYPE_H
#define DEVICETYPE_H

#include <QObject>
#include <QString>

class DeviceType
{
public:
    DeviceType(QString deviceTypeName = "Add", QString imageSource = "qrc:/img/plus.svg", double imageWidthScalar = 4.0, double imageHeightScaler = 4.0);

    QString getImageSource();
    double getImageWidthScaler();
    double getImageHeightScaler();
    QString getDeviceTypeName();

    void setImageSource(QString newSource);
    void setImageWidthScaler(double newScaler);
    void setImageHeightScaler(double newScaler);
    void setDeviceTypeName(QString newName);

    bool operator!=(const DeviceType &a);

private:
    QString m_deviceTypeName;
    QString m_imageSource;
    double m_imageWidthScaler;
    double m_imageHeightScaler;
};

#endif // DEVICETYPE_H
