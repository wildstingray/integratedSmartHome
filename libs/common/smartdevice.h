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
    Q_PROPERTY(QString qmlUrl READ qmlUrl WRITE setQmlUrl NOTIFY qmlUrlChanged)
    Q_PROPERTY(QString deviceTypeName READ deviceTypeName WRITE setDeviceTypeName NOTIFY deviceTypeNameChanged)
    Q_PROPERTY(QString payload READ payload WRITE setPayload NOTIFY payloadChanged)

    QString deviceName();
    void setDeviceName(QString newName);

    DeviceType deviceType();
    void setDeviceType(DeviceType &newType);

    QString topicString();
    void setTopicString(QString newTopic); //{m_topic = QMqttTopicName(newTopic);}

    QString qmlUrl();
    void setQmlUrl(QString newUrl);

    QString deviceTypeName();
    void setDeviceTypeName(QString newTypeName);

    QString payload();
    void setPayload(QString newPayload);

signals:
    void deviceNameChanged(QString name);
    void deviceTypeChanged(DeviceType type);
    void topicStringChanged(QString topic);
    void qmlUrlChanged(QString url);
    void deviceTypeNameChanged(QString deviceTypeName);
    void payloadChanged(QString);

public slots:

private:
    QString m_name;
    DeviceType m_deviceType;
    QMqttTopicName m_topicString;
    QString m_qmlUrl;
    QString m_deviceTypeName;
    QString m_payload;
};

#endif // SMARTDEVICE_H
