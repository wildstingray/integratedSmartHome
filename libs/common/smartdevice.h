#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <QObject>
#include "devicetype.h"

class SmartDevice : public QObject
{
    Q_OBJECT
public:
    explicit SmartDevice(QObject *parent = nullptr);

    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged)
//    Q_PROPERTY(DeviceType deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)

    QString deviceName();
    void setDeviceName(QString newName);

    DeviceType deviceType();
    void setDeviceType(DeviceType &newType);


signals:
    void deviceNameChanged(QString name);
    void deviceTypeChanged(DeviceType type);

public slots:

private:
    QString m_name;
    DeviceType m_deviceType;
};

#endif // SMARTDEVICE_H
