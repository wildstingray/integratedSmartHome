#ifndef DEVICETYPE_H
#define DEVICETYPE_H

#include <QString>

class DeviceType
{
public:
    DeviceType(QString imageSource = "", double imageWidthScalar = 2.0, double imageHeightScaler = 2.0);

    QString getImageSource();
    double getImageWidthScaler();
    double getImageHeightScaler();

    bool operator!=(const DeviceType &a);

private:
    QString m_imageSource;
    double m_imageWidthScaler;
    double m_imageHeightScaler;
};

#endif // DEVICETYPE_H
