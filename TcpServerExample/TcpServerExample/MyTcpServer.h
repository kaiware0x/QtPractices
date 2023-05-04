
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QThreadPool>

class MyTcpServer : public QTcpServer {
public:
    explicit MyTcpServer(QObject* parent = nullptr);
    void startServer();

signals:

protected:
    void incomingConnection(qintptr handle) override;

private:
    QThreadPool* myThreadPool;
};

#endif // MYTCPSERVER_H
