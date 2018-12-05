#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariantList>
#include "libs/common/devicetype.h"
#include "smartdevicesmodel.h"
#include "globalproperties.h"

int main(int argc, char *argv[])
{
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



    //C++
    SmartDevicesModel smartDevicesModel(&app);
    smartDevicesModel.add();
    smartDevicesModel.add();
    smartDevicesModel.add();
    smartDevicesModel.add();
    smartDevicesModel.add();
    GlobalProperties globalProperties(&app);

    //QML
    QQmlApplicationEngine engine(&app);

    qmlRegisterType<SmartDevicesModel>("com.integratedSmartHome", 1, 0, "SmartDevicesModel");

    QQmlContext *context = engine.rootContext();
        context->setContextProperty("smartDevicesModel", &smartDevicesModel);
        context->setContextProperty("globalProperties", &globalProperties);


    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
