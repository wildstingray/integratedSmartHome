#ifndef QMLMQTTCLIENT_H
#define QMLMQTTCLIENT_H

#include <QtCore/QMap>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

class QmlMqttClient;

class QmlMqttSubscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)

public:
    QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c);
    ~QmlMqttSubscription();

Q_SIGNALS:
    void topicChanged(QString);
    void messageReceived(const QString &msg);

public slots:
    void handleMessage(const QMqttMessage &qmsg);

private:
    Q_DISABLE_COPY(QmlMqttSubscription)
    QMqttSubscription *sub;
    QmlMqttClient *client;
    QMqttTopicFilter m_topic;
};

class QmlMqttClient : public QMqttClient
{
    Q_OBJECT
public:
    QmlMqttClient(QObject *parent = nullptr);

    Q_INVOKABLE QmlMqttSubscription *subscribe(const QString &topic);
    Q_PROPERTY(int portNum READ portNum WRITE setPortNum NOTIFY portNumChanged)

    int portNum();
    void setPortNum(int newPort);

signals:
    void portNumChanged(int newPort);

private:
    Q_DISABLE_COPY(QmlMqttClient)

    void handlePortChanged(quint16 newPort);
};

#endif // QMLMQTTCLIENT_H
