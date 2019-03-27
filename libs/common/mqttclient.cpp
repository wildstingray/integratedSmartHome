#include "mqttclient.h"

MqttClient::MqttClient(QObject *parent) : QMqttClient(parent)
{

}

QMqttSubscription* MqttClient::subscribe(const QString &topic)
{
    auto sub = QMqttClient::subscribe(topic, 0);
    //auto result = new QMqttSubscription(sub, this);
    //return result;
}
