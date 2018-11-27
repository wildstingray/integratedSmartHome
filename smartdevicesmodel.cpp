#include "smartdevicesmodel.h"

SmartDevicesModel::SmartDevicesModel(QObject *parent) : QAbstractListModel(parent)
{

}

void SmartDevicesModel::add()
{
    insertRows(devices.length(), 1, QModelIndex());
}

int SmartDevicesModel::rowCount()
{
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
        case Qt::DisplayRole:
            break;
        default:
            break;
    }
    return returnVar;
}

bool SmartDevicesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)
    if (index.isValid() && role == Qt::EditRole) {

        //            devices.replace(index.row(), value.toString());
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
    roles[ImageHeightScaler] = "imageWidthScaler";
    return roles;
}
