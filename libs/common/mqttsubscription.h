#ifndef MQTTSUBSCRIPTION_H
#define MQTTSUBSCRIPTION_H

#include <QObject>
#include <QtMqtt/QMqttSubscription>

class MqttSubscription : public QObject
{
    Q_OBJECT
public:
    explicit MqttSubscription(QMqttSubscription * subptr = nullptr, QObject *parent = nullptr);

    Q_PROPERTY(QObject * subPtr READ subPtr NOTIFY subPtrChanged)

    QMqttSubscription * subPtr();
signals:

    void subPtrChanged(QObject * newSubPtr);

public slots:

private:
    QMqttSubscription * m_subPtr;
};

#endif // MQTTSUBSCRIPTION_H
