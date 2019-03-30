#include "smartdevicesmodel.h"
#include <QModelIndex>

SmartDevicesModel::SmartDevicesModel(QObject *parent) : QAbstractListModel(parent)
{

}

void SmartDevicesModel::add()
{
    insertRows(devices.length(), 1, QModelIndex());
}

void SmartDevicesModel::resetAtIndex(int row)
{
    removeRows(row, 1, QModelIndex());
    if (devices.length() == row)
    {
        this->add();
    }
}

int SmartDevicesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return devices.count();
}

QVariant SmartDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= devices.size())
        return QVariant();

    QVariant returnVar = QVariant();
    switch (role)
    {
        case DeviceName:
            returnVar = devices.at(index.row())->deviceName();
            break;
        case ImageSource:
            returnVar = devices.at(index.row())->deviceType().getImageSource();
            break;
        case ImageWidthScaler:
            returnVar = devices.at(index.row())->deviceType().getImageWidthScaler();
            break;
        case ImageHeightScaler:
            returnVar = devices.at(index.row())->deviceType().getImageHeightScaler();
            break;
        case TopicString:
            returnVar = devices.at(index.row())->topicString();
            break;
        case isRegistered:
//            returnVar = devices.at(index.row())->deviceType()->getImageSource() != DeviceType().getImageSource();
            break;
        default:
            break;
    }
    return returnVar;
}

bool SmartDevicesModel::setData(int row, const QVariant &value, int role)
{
    return setData(index(row), value, role);
}

bool SmartDevicesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ((index.row() < devices.count())
            && index.isValid()
            && role >= DeviceName) {
        QSharedPointer<SmartDevice> device = devices.at(index.row());
        static DeviceType type = device->deviceType();
        bool ok = false;
        switch (role) {
            case DeviceName:
                device->setDeviceName(value.toString());
                emit device->deviceTypeChanged(device->deviceType());
                break;
            case ImageSource:
                type.setImageSource(value.toString());
                device->setDeviceType(type);
                emit device->deviceTypeChanged(device->deviceType());
                break;
            case ImageWidthScaler:
                type.setImageWidthScaler(value.toDouble(&ok));
                if (ok)
                {
                    device->setDeviceType(type);
                    emit device->deviceTypeChanged(device->deviceType());
                }
                else return false;
                break;
            case ImageHeightScaler:
                type.setImageHeightScaler(value.toDouble(&ok));
                if (ok)
                {
                    device->setDeviceType(type);
                    emit device->deviceTypeChanged(device->deviceType());
                }
                else return false;
                break;
            default:
                break;
        }
        //device->deleteLater();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags SmartDevicesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SmartDevicesModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        devices.insert(position, QSharedPointer<SmartDevice>(new SmartDevice(this)));
    }

    endInsertRows();
    return true;
}

bool SmartDevicesModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        QSharedPointer<SmartDevice> temp = devices.at(position);
        devices.removeAt(position);
        //temp->deleteLater(); TODO do I need this? SEVERE memory issue if I do
        //QSharedPointer is supposed to handle deletion, but will it work in this context?
    }

    endRemoveRows();
    return true;
}

QHash<int, QByteArray> SmartDevicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DeviceName] = "name";
    roles[ImageSource] = "imageSource";
    roles[ImageWidthScaler] = "imageWidthScaler";
    roles[ImageHeightScaler] = "imageHeightScaler";
    roles[isRegistered] = "isRegistered";
    roles[TopicString] = "topicName";
    return roles;
}
