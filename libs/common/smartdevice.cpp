#include "smartdevice.h"

SmartDevice::SmartDevice(QObject *parent) : QObject(parent)
{
    m_deviceType = DeviceType();
    m_name = "";
    m_topicString = QMqttTopicName("/Test");
    m_deviceTypeName = "Default";
    m_qmlUrl = "qrc:/qml/ComplexSmartButton.qml";
    m_payload = "0";
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
    return m_topicString.name();
}

void SmartDevice::setTopicString(QString newTopic)
{
    if (m_topicString.name() != newTopic)
    {
        m_topicString.setName(newTopic);
        emit topicStringChanged(newTopic);
    }
}

QString SmartDevice::qmlUrl()
{
    return m_qmlUrl;
}

void SmartDevice::setQmlUrl(QString newUrl)
{
    if (m_qmlUrl != newUrl)
    {
        m_qmlUrl = newUrl;
        emit qmlUrlChanged(m_qmlUrl);
    }
}

QString SmartDevice::deviceTypeName()
{
    return m_deviceTypeName;
}

void SmartDevice::setDeviceTypeName(QString newTypeName)
{
    if (m_deviceTypeName != newTypeName)
    {
        m_deviceTypeName = newTypeName;
        emit deviceTypeNameChanged(m_deviceTypeName);
    }
}

QString SmartDevice::payload()
{
    return m_payload;
}

void SmartDevice::setPayload(QString newPayload)
{
    if (m_payload != newPayload)
    {
        m_payload = newPayload;
        emit payloadChanged(newPayload);
    }
}
