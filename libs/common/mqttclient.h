#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttMessage>

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
    void handleMessage(QMqttMessage msg);

private:
    QList<QMqttSubscription *> subscriptions;
    QList<QMqttMessage> m_availableMessages;
};

#endif // MQTTCLIENT_H
