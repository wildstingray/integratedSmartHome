#include "smartdevicesmodel.h"
#include <QModelIndex>

#include <QJsonArray>
#include <QJsonObject>

#define JSON_ARRAY_NAME "Devices"
#define JSON_SAVE_NAME "SmartDevicesModel"

SmartDevicesModel::SmartDevicesModel(QObject *parent) : QAbstractListModel(parent)
{
    m_objectCounter = 1;
}

void SmartDevicesModel::setJsonHandlerPtr(JsonFileHandler * jsonHandler)
{
    m_jsonHandler = jsonHandler;
    readJsonFile();
}

void SmartDevicesModel::add()
{
    insertRows(devices.length(), 1, QModelIndex());
}

void SmartDevicesModel::resetAtIndex(int row)
{
    removeRows(row, 1, QModelIndex());
    if (devices.length() == 0)
    {
        this->add();
    }
}

int SmartDevicesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return devices.count();
}

QVariant SmartDevicesModel::data(int row, int role) const
{
    return data(index(row), role);
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
        case QmlUrl:
            returnVar = devices.at(index.row())->qmlUrl();
            break;
        case DeviceTypeName:
            returnVar = devices.at(index.row())->deviceTypeName();
            break;
        case Payload:
            returnVar = devices.at(index.row())->payload();
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
                break;
            case ImageSource:
                type.setImageSource(value.toString());
                device->setDeviceType(type);
                break;
            case ImageWidthScaler:
                type.setImageWidthScaler(value.toDouble(&ok));
                if (ok)
                {
                    device->setDeviceType(type);
                }
                else return false;
                break;
            case ImageHeightScaler:
                type.setImageHeightScaler(value.toDouble(&ok));
                if (ok)
                {
                    device->setDeviceType(type);
                }
                else return false;
                break;
            case TopicString:
                device->setTopicString(value.toString());
                break;
            case QmlUrl:
                device->setQmlUrl(value.toString());
                break;
            case DeviceTypeName:
                device->setDeviceTypeName(value.toString());
                break;
            case Payload:
                device->setPayload(value.toString());
                break;
            default:
                break;
        }
        //device->deleteLater();
        emit dataChanged(index, index, {role});
        saveJsonFile();
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
    saveJsonFile();

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

    saveJsonFile();

    endRemoveRows();
    return true;
}

int SmartDevicesModel::objectCounter()
{
    return m_objectCounter;
}

void SmartDevicesModel::incObjectCounter()
{
    m_objectCounter++;
}

void SmartDevicesModel::newMessage(QString topic, QString payload)
{
    for (int i = 0; i < devices.length(); i++)
    {
        if (devices.at(i)->topicString() == topic)
        {
            this->setData(i, payload, Payload);
        }
    }
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
    roles[QmlUrl] = "qmlUrl";
    roles[DeviceTypeName] = "deviceTypeName";
    roles[Payload] = "payload";
    return roles;
}

void SmartDevicesModel::readJsonFile()
{
    if (m_jsonHandler == nullptr) return;

    QJsonObject obj;
    m_jsonHandler->readObject(obj, JSON_SAVE_NAME);

    QJsonArray jsonArray = obj[JSON_ARRAY_NAME].toArray();

    for (int i = 0; i < jsonArray.count(); i++)
    {
        //TODO use QMetaEnum to do this Dynamically
        this->add();
        QJsonObject obj = jsonArray.at(i).toObject();
        QStringList keyList = obj.keys();
        if (keyList.contains("DeviceName"))
            this->setData(i, obj["DeviceName"].toString(), SmartDevicesModel::DeviceName);

        if (keyList.contains("ImageSource"))
            this->setData(i, obj["ImageSource"].toString(), SmartDevicesModel::ImageSource);

        if (keyList.contains("ImageWidthScaler"))
            this->setData(i, obj["ImageWidthScaler"].toString(), SmartDevicesModel::ImageWidthScaler);

        if (keyList.contains("ImageHeightScaler"))
            this->setData(i, obj["ImageHeightScaler"].toString(), SmartDevicesModel::ImageHeightScaler);

        if (keyList.contains("isRegistered"))
            this->setData(i, obj["isRegistered"].toString(), SmartDevicesModel::isRegistered);

        if (keyList.contains("TopicString"))
            this->setData(i, obj["TopicString"].toString(), SmartDevicesModel::TopicString);

        if (keyList.contains("QmlUrl"))
            this->setData(i, obj["QmlUrl"].toString(), SmartDevicesModel::QmlUrl);

        if (keyList.contains("DeviceTypeName"))
            this->setData(i, obj["DeviceTypeName"].toString(), SmartDevicesModel::DeviceTypeName);

        if (keyList.contains("Payload"))
            this->setData(i, obj["Payload"].toString(), SmartDevicesModel::Payload);
    }
    if (this->data(rowCount() - 1, DeviceName).toString() != "")
    {
        this->add();
    }

}

void SmartDevicesModel::saveJsonFile()
{
    if (m_jsonHandler == nullptr) return;

    QJsonArray jsonArray;
    for (int i = 0; i < rowCount(); i++)
    {
        //TODO use QMetaEnum to do this dynamically
        QJsonObject obj;
        obj["DeviceName"] = data(i, SmartDevicesModel::DeviceName).toString();
        obj["ImageSource"] = data(i, SmartDevicesModel::ImageSource).toString();
        obj["ImageWidthScaler"] = data(i, SmartDevicesModel::ImageWidthScaler).toString();
        obj["ImageHeightScaler"] = data(i, SmartDevicesModel::ImageHeightScaler).toString();
        obj["isRegistered"] = data(i, SmartDevicesModel::isRegistered).toString();
        obj["TopicString"] = data(i, SmartDevicesModel::TopicString).toString();
        obj["QmlUrl"] = data(i, SmartDevicesModel::QmlUrl).toString();
        obj["DeviceTypeName"] = data(i, SmartDevicesModel::DeviceTypeName).toString();
        obj["Payload"] = data(i, SmartDevicesModel::Payload).toString();
        jsonArray.append(obj);
    }
    QJsonObject docObject;
    docObject[JSON_ARRAY_NAME] = jsonArray;

    m_jsonHandler->saveObject(docObject, JSON_SAVE_NAME);
}
