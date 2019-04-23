#ifndef JSONFILEHANDLER_H
#define JSONFILEHANDLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

class JsonFileHandler : public QObject
{
    Q_OBJECT
public:
    explicit JsonFileHandler(QObject *parent = nullptr);

    void setFileLocation(QString newFileLocation);

signals:

public slots:
    bool saveObject(QJsonObject & obj, QString value);
    bool readObject(QJsonObject & obj, QString Value);

private:
    QFile m_file;
    QDir m_dir;
    QString m_filePath;
};

#endif // JSONFILEHANDLER_H
