#include "globalproperties.h"

GlobalProperties * GlobalProperties::_instance = Q_NULLPTR;

GlobalProperties::GlobalProperties(QObject * parent)
    : QObject(parent)
{
    Q_ASSERT(!_instance);
    _instance = this;

    //TODO
    m_deviceTypes.clear();
    m_deviceTypes.append(DeviceType("qrc:/img/lightbulbicon.svg", 1.4, 1.2));
}

GlobalProperties * GlobalProperties::instance()
{
    return _instance;
}

QList<DeviceType> GlobalProperties::deviceTypes()
{
    return m_deviceTypes;
}
