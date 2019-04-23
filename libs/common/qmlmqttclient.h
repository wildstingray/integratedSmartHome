#ifndef QMLMQTTCLIENT_H
#define QMLMQTTCLIENT_H

#include <QtCore/QMap>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttTopicName>

class QmlMqttClient;

class QmlMqttSubscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)

public:
// TODO On possible implementation for moving data processing out of qml
//    enum DataTypes{
//        Boolean=0, //Lightbulb or relay
//        Array //Could be used for rgb
//    };
//    Q_ENUM(DataTypes)


    QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c);
    ~QmlMqttSubscription();

Q_SIGNALS:
    void topicChanged(QString);
    void messageReceived(const QString &topic, const QString &msg);

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

    Q_PROPERTY(QString lastTopic READ lastTopic NOTIFY lastTopicChanged)
    Q_PROPERTY(QString lastPayload READ lastPayload NOTIFY lastPayloadChanged)

    int portNum();
    void setPortNum(int newPort);

    QString lastTopic();
    QString lastPayload();

public slots:
    qint32 publishString(const QString &topicName, const QString &message = "", quint8 qos = 0, bool retain = false);
    qint32 publish(const QString &topicName, const int &message = 0, quint8 qos = 0, bool retain = false);
    void handleNewMessage(const QMqttMessage &qmsg);

    QString getMsgTopicAt(int index);
    QString getMsgPayloadAt(int index);

signals:
    void portNumChanged(int newPort);
    void lastTopicChanged(QString newTopic);
    void lastPayloadChanged(QString newPayload);
    void newMessage(QString topic, QString payload);

private:
    Q_DISABLE_COPY(QmlMqttClient)

    void pingSuccessful();
    void stateChange();

    void handlePortChanged(quint16 newPort);

    QList<QMqttMessage> m_lastMessages;
};

#endif // QMLMQTTCLIENT_H
