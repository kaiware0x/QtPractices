
#include "HelloWorld.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    const QUrl url(u"qrc:/tutorial/Main.qml"_qs);
    engine.load(url);

    HelloWorld hellocpp;
    engine.rootContext()->setContextProperty("hellocpp", &hellocpp);

    return app.exec();
}
