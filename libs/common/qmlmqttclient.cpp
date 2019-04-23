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
            connect(sub, &QMqttSubscription::messageReceived, this, &QmlMqttClient::handleNewMessage);
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

QString QmlMqttClient::lastTopic()
{
    return m_lastMessages.first().topic().name();
}

QString QmlMqttClient::lastPayload()
{
    return m_lastMessages.first().payload();
}

qint32 QmlMqttClient::publishString(const QString &topicName, const QString &message, quint8 qos, bool retain)
{
    return this->QMqttClient::publish(QMqttTopicName(topicName), message.toUtf8(), qos, retain);
}

qint32 QmlMqttClient::publish(const QString &topicName, const int &message, quint8 qos, bool retain)
{
    return this->QMqttClient::publish(QMqttTopicName(topicName), QByteArray().setNum(message), qos, retain);
}

void QmlMqttClient::handleNewMessage(const QMqttMessage &qmsg)
{
    m_lastMessages.prepend(qmsg);
    emit lastTopicChanged(qmsg.topic().name());
    emit lastPayloadChanged(qmsg.payload());
    emit newMessage(qmsg.topic().name(), qmsg.payload());

    if (m_lastMessages.length() >= 10)
    {
        m_lastMessages.removeLast();
    }
}

QString QmlMqttClient::getMsgTopicAt(int index)
{
    if (index < m_lastMessages.length())
    {
        return m_lastMessages.at(index).topic().name();
    }
    else return "";
}

QString QmlMqttClient::getMsgPayloadAt(int index)
{
    if (index < m_lastMessages.length())
    {
        return m_lastMessages.at(index).payload();
    }
    else return "";
}

void QmlMqttClient::pingSuccessful()
{
    qDebug() << "Connected";
    subscribe("raspi/#");
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
    emit messageReceived(qmsg.topic().name(), qmsg.payload());
}
