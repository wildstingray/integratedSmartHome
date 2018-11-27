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
        ImageHeightScaler
    };
    Q_ENUM(roles)

public:
    explicit SmartDevicesModel(QObject *parent = nullptr);

    int rowCount();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

signals:

public slots:

private:
    QList<QSharedPointer<SmartDevice>> devices;

    using QAbstractListModel::rowCount;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // SMARTDEVICESMODEL_H
