#ifndef SMARTDEVICESMODEL_H
#define SMARTDEVICESMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include "smartdevice.h"
#include <QSharedPointer>

class SmartDevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum roles{
        DeviceName=Qt::UserRole,
        ImageSource,
        ImageWidthScaler,
        ImageHeightScaler,
        isRegistered,
        TopicString,
        QmlUrl,
        DeviceTypeName,
    };
    Q_ENUM(roles)

public:
    explicit SmartDevicesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    Q_PROPERTY(int objectCounter READ objectCounter NOTIFY objectCounterChanged)

    int objectCounter();

signals:
    void objectCounterChanged();

public slots: // Same as Q_INVOKABLE
    bool setData(int row, const QVariant &value, int role);
    QVariant data(int row, int role) const;
    void add();
    void resetAtIndex(int row);

    void incObjectCounter();

private:
    QList<QSharedPointer<SmartDevice>> devices;

    QHash<int, QByteArray> roleNames() const override;

    int m_objectCounter;
};

#endif // SMARTDEVICESMODEL_H
