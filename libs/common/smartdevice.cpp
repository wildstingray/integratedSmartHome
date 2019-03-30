#include "smartdevice.h"

SmartDevice::SmartDevice(QObject *parent) : QObject(parent)
{
    m_deviceType = DeviceType();
    m_name = "";
}

QString SmartDevice::deviceName()
{
    return m_name;
}

void SmartDevice::setDeviceName(QString newName)
{
    if (m_name != newName)
    {
        m_name = newName;
        emit deviceNameChanged(m_name);
    }
}

DeviceType SmartDevice::deviceType()
{
    return m_deviceType;
}

void SmartDevice::setDeviceType(DeviceType &newType)
{
    if (m_deviceType != newType)
    {
        m_deviceType = newType;
        emit deviceTypeChanged(m_deviceType);
    }
}

QString SmartDevice::topicString()
{
    return m_topic.name();
}

void SmartDevice::setTopicString(QString newTopic)
{
    if (m_topic.name() != newTopic)
    {
        m_topic.setName(newTopic);
        emit topicStringChanged(newTopic);
    }
}
