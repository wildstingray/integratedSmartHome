#include "mqttclient.h"

MqttClient::MqttClient(QObject *parent) : QMqttClient(parent)
{

}

QMqttSubscription* MqttClient::subscribe(const QString &topic)
{
    auto sub = QMqttClient::subscribe(topic, 0);
    connect(sub, &QMqttSubscription::messageReceived, this, &MqttClient::handleMessage);
    subscriptions.append(sub);
    return sub;
}

void MqttClient::handleMessage(QMqttMessage msg)
{
    m_availableMessages.append(msg);
    emit messageReceived(msg.payload(), msg.topic());
    if (m_availableMessages.length() >= 16)
    {
        m_availableMessages.removeFirst();
    }
}
