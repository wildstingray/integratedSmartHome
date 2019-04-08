#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <QObject>
#include "devicetype.h"
#include <QtMqtt/QMqttTopicName>

class SmartDevice : public QObject
{
    Q_OBJECT
public:
    explicit SmartDevice(QObject *parent = nullptr);

    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged)
//    Q_PROPERTY(DeviceType deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(QString topicString READ topicString WRITE setTopicString NOTIFY topicStringChanged)

    QString deviceName();
    void setDeviceName(QString newName);

    DeviceType deviceType();
    void setDeviceType(DeviceType &newType);

    QString topicString();
    void setTopicString(QString newTopic); //{m_topic = QMqttTopicName(newTopic);}

signals:
    void deviceNameChanged(QString name);
    void deviceTypeChanged(DeviceType type);
    void topicStringChanged(QString topic);

public slots:

private:
    QString m_name;
    DeviceType m_deviceType;
    QMqttTopicName m_topicString;
};

#endif // SMARTDEVICE_H
