#include "jsonfilehandler.h"
#include <QDebug>
#include <QJsonArray>
#include <QMetaEnum>

JsonFileHandler::JsonFileHandler(QObject *parent) : QObject(parent)
{
    m_filePath = m_dir.homePath();
    m_filePath.append("/SmartHomeApp");

    if (!m_dir.exists(m_filePath))
    {
        m_dir.mkdir(m_filePath);
    }

    m_filePath.append("/SmartDevices.json");
    m_file.setFileName(m_filePath);

    if (m_file.isOpen())
    {
        m_file.close();
    }
}

void JsonFileHandler::setFileLocation(QString newFileLocation)
{
    m_file.setFileName(newFileLocation);
}

bool JsonFileHandler::saveObject(QJsonObject & obj, QString value)
{
    QJsonDocument doc;
    QJsonObject tempObj;
    if (m_file.exists())
    {
        m_file.open(QIODevice::ReadOnly);
        QByteArray jsonInfomation = m_file.readAll();
        doc = QJsonDocument::fromJson(jsonInfomation);
        m_file.close();
    }

    if (doc.isObject())
    {
        tempObj = doc.object();
    }
    tempObj[value] = obj;
    doc.setObject(tempObj);
    if (m_file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        m_file.write(doc.toJson());
        m_file.close();
        return true;
    }
    return false;
}

bool JsonFileHandler::readObject(QJsonObject & obj, QString value)
{
    if (m_file.exists())
    {
        m_file.open(QIODevice::ReadOnly);
        QByteArray jsonInfomation = m_file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(jsonInfomation));
        obj = doc[value].toObject();
        return true;
    }
    else return false;
}
