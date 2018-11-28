#ifndef GLOBALPROPERTIES_H
#define GLOBALPROPERTIES_H

#include <QObject>

//Make this a singleton that QML can access

class GlobalProperties : public QObject
{
    Q_OBJECT
public:
    explicit GlobalProperties(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GLOBALPROPERTIES_H
