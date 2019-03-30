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
    Q_PROPERTY(QMqttTopicName topic READ topic WRITE settopic NOTIFY topicChanged)

    QString deviceName();
    void setDeviceName(QString newName);

    DeviceType deviceType();
    void setDeviceType(DeviceType &newType);

    QMqttTopicName topic();
    void setTopic(QString newTopic); //{m_topic = QMqttTopicName(newTopic);}

signals:
    void deviceNameChanged(QString name);
    void deviceTypeChanged(DeviceType type);
    void topicChanged(QString topic);

public slots:

private:
    QString m_name;
    DeviceType m_deviceType;
    QMqttTopicName m_topic;
};

#endif // SMARTDEVICE_H
