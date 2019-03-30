#include "qmlmqttclient.h"
#include <QDebug>

QmlMqttClient::QmlMqttClient(QObject *parent)
    : QMqttClient(parent)
{
    connect(this, &QMqttClient::portChanged, this, &QmlMqttClient::handlePortChanged);
}

QmlMqttSubscription* QmlMqttClient::subscribe(const QString &topic)
{
    //TODO fix this, crashes
    auto sub = QMqttClient::subscribe(topic, 0);
    auto result = new QmlMqttSubscription(sub, this);
    return result;
}

int QmlMqttClient::portNum()
{
    return port();
}

void QmlMqttClient::setPortNum(int newPort)
{
    if (newPort != port())
    {
        setPort(static_cast<quint16>(newPort));
        emit portNumChanged(newPort);
    }
}

void QmlMqttClient::handlePortChanged(quint16 newPort)
{
    emit portNumChanged(static_cast<int>(newPort));
}

QmlMqttSubscription::QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c)
    : sub(s)
    , client(c)
{
    connect(sub, &QMqttSubscription::messageReceived, this, &QmlMqttSubscription::handleMessage);
    m_topic = sub->topic();
}

QmlMqttSubscription::~QmlMqttSubscription()
{
}

void QmlMqttSubscription::handleMessage(const QMqttMessage &qmsg)
{
    emit messageReceived(qmsg.payload());
}
