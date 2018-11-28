#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "smartdevicesmodel.h"

int main(int argc, char *argv[])
{
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //C++
    SmartDevicesModel model;

    QList<DeviceType> deviceTypes;
    deviceTypes.append(DeviceType("SmartBulb", "qrc:/img/lightbulbicon.svg", 1.4, 1.2));

    //QML
    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
        ctxt->setContextProperty("smartDevicesModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
