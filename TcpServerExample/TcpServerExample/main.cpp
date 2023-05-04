
#include "MyTcpServer.h"
#include <QCoreApplication>

/// https://www.youtube.com/watch?v=qnlqXBW8IWI

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
    server.startServer();

    return a.exec();
}
