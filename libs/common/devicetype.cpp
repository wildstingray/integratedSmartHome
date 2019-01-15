#include "devicetype.h"

DeviceType::DeviceType(QString deviceTypeName, QString imageSource, double imageWidthScalar, double imageHeightScaler)
{
    m_deviceTypeName = deviceTypeName;
    m_imageSource = imageSource;
    m_imageWidthScaler = imageWidthScalar;
    m_imageHeightScaler = imageHeightScaler;
}

QString DeviceType::getImageSource()
{
    return m_imageSource;
}

double DeviceType::getImageWidthScaler()
{
    return m_imageWidthScaler;
}

double DeviceType::getImageHeightScaler()
{
    return m_imageHeightScaler;
}

QString DeviceType::getDeviceTypeName()
{
    return m_deviceTypeName;
}

void DeviceType::setImageSource(QString newSource)
{
    m_imageSource = newSource;
}

void DeviceType::setImageWidthScaler(double newScaler)
{
    m_imageWidthScaler = newScaler;
}

void DeviceType::setImageHeightScaler(double newScaler)
{
    m_imageHeightScaler = newScaler;
}

void DeviceType::setDeviceTypeName(QString newName)
{
    m_deviceTypeName = newName;
}

bool DeviceType::operator!=(const DeviceType &a)
{
    if (this->m_imageSource != a.m_imageSource
            || this->m_imageWidthScaler != a.m_imageWidthScaler
            || this->m_imageHeightScaler != a.m_imageHeightScaler)
    {
        return true;
    }
    else return false;
}


