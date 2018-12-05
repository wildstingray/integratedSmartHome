#ifndef GLOBALPROPERTIES_H
#define GLOBALPROPERTIES_H

#include <QObject>
#include "libs/common/devicetype.h"
#include <QVariantList>

class GlobalProperties : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QList<DeviceType> deviceTypes READ deviceTypes NOTIFY deviceTypesChanged)

public:
    GlobalProperties(QObject * parent = Q_NULLPTR);

    static GlobalProperties * instance();

    QList<DeviceType> deviceTypes();

signals:
    void deviceTypesChanged(QList<DeviceType> newTypes);

private:
    static GlobalProperties * _instance;
    QList<DeviceType> m_deviceTypes;
};

#endif // GLOBALPROPERTIES_H
