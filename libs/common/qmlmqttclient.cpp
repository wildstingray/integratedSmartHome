#include "qmlmqttclient.h"
#include <QDebug>

QmlMqttClient::QmlMqttClient(QObject *parent)
    : QMqttClient(parent)
{
    setHostname("localhost");
    setPort(1883);
    connect(this, &QMqttClient::portChanged, this, &QmlMqttClient::handlePortChanged);
    connect(this, &QMqttClient::connected, this, &QmlMqttClient::pingSuccessful);
    connect(this, &QMqttClient::stateChanged, this, &QmlMqttClient::stateChange);
}

QmlMqttSubscription* QmlMqttClient::subscribe(const QString &topic)
{
    if (this->state() == Connected)
    {
        auto sub = QMqttClient::subscribe(QMqttTopicFilter(topic), 0);
        if (sub != nullptr)
        {
            auto result = new QmlMqttSubscription(sub, this);
            qDebug() << "Subscribed to " << topic;
            return result;
        }
        else
        {
            qDebug() << "Error subscribing";
            return nullptr;
        }
    }
    else
    {
        qDebug() << "Not Connected";
        return nullptr;
    }
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

//qint32 QmlMqttClient::publish(const QString &topicName, const QString &message, quint8 qos, bool retain)
//{
//    return this->QMqttClient::publish(QMqttTopicName(topicName), message.toUtf8(), qos, retain);
//}

qint32 QmlMqttClient::publish(const QString &topicName, const int &message, quint8 qos, bool retain)
{
    return this->QMqttClient::publish(QMqttTopicName(topicName), QByteArray().setNum(message), qos, retain);
}

void QmlMqttClient::pingSuccessful()
{
    qDebug() << "Connected";
    subscribe("/raspi");
}

void QmlMqttClient::stateChange()
{
    qDebug() << "State changed to " << state();
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
