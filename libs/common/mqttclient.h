#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

//TODO implement this system
//https://doc.qt.io/QtMQTT/qtmqtt-quicksubscription-example.html

class MqttClient : public QMqttClient
{
    Q_OBJECT
public:
    explicit MqttClient(QObject *parent = nullptr);

    QMqttSubscription *subscribe(const QString &topic);
signals:

public slots:
};

#endif // MQTTCLIENT_H
