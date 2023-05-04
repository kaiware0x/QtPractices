
#include "MyTcpServer.h"
#include "MyTask.h"

MyTcpServer::MyTcpServer(QObject* parent)
    : QTcpServer(parent)
    , myThreadPool(new QThreadPool(this))
{
    /// 適用に5スレッド分用意しておく。
    myThreadPool->setMaxThreadCount(5);
}

void MyTcpServer::startServer()
{
    /// 127.0.0.1:1234からのパケットを待ち受けるように設定.
    if (this->listen(QHostAddress::LocalHost, 1234)) {
        qInfo() << "Server start successfully on localhost:1234.";
    } else {
        qInfo() << "Server start failed on localhost:1234.";
    }
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    qInfo() << "Incoming connection received:" << handle;

    /// スレッドプールの中のスレッドにMyTaskを実行させる。
    auto task = new MyTask(handle);
    myThreadPool->start(task);
}
