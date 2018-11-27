#ifndef SMARTDEVICESMODEL_H
#define SMARTDEVICESMODEL_H

#include <QObject>

class SmartDevicesModel : public QObject
{
    Q_OBJECT
public:
    explicit SmartDevicesModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SMARTDEVICESMODEL_H