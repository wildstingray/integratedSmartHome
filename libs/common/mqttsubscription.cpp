#include "mqttsubscription.h"

MqttSubscription::MqttSubscription(QMqttSubscription * newSubPtr, QObject *parent) : QObject(parent)
{
    this->m_subPtr = newSubPtr;
    emit subPtrChanged(this->m_subPtr);
}

QMqttSubscription *MqttSubscription::subPtr()
{
    return m_subPtr;
}
