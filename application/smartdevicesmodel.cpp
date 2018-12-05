#include "smartdevicesmodel.h"
#include <QModelIndex>

SmartDevicesModel::SmartDevicesModel(QObject *parent) : QAbstractListModel(parent)
{

}

void SmartDevicesModel::add()
{
    insertRows(devices.length(), 1, QModelIndex());
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
            returnVar = devices.at(index.row())->deviceType()->getImageSource();
            break;
        case ImageWidthScaler:
            returnVar = devices.at(index.row())->deviceType()->getImageWidthScaler();
            break;
        case ImageHeightScaler:
            returnVar = devices.at(index.row())->deviceType()->getImageHeightScaler();
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
    //TODO Fix this
    if ((index.row() < devices.count())
            && index.isValid()
            && role >= DeviceName) {
        QSharedPointer<SmartDevice> device = devices.at(index.row());
        switch (role) {
            case DeviceName:
//                device->deviceType()->setDeviceTypeName(value.toString());
                emit device->deviceTypeChanged(*device->deviceType());
                break;
            case ImageSource:
//                device->deviceType()->setImageSource(value.toString());
                emit device->deviceTypeChanged(*device->deviceType());
                break;
            case ImageWidthScaler:
//                device->deviceType()->setImageWidthScaler(value.toDouble());
                emit device->deviceTypeChanged(*device->deviceType());
                break;
            case ImageHeightScaler:
//                device->deviceType()->setImageHeightScaler(value.toDouble());
                emit device->deviceTypeChanged(*device->deviceType());
                break;
            default:
                break;
        }
        device->deleteLater();
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
        temp->deleteLater();
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
    return roles;
}
