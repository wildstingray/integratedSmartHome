#include "devicetype.h"

DeviceType::DeviceType(QString imageSource, double imageWidthScalar, double imageHeightScaler)
{
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


