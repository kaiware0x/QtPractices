
#ifndef REQUEST_H
#define REQUEST_H

#include <QHostAddress>
#include <QMessageBox>
#include <QObject>
#include <QTcpSocket>

class Request : public QObject {
    Q_OBJECT

public:
    explicit Request(QObject* parent = 0);
    QString message;

signals:
    void done();

public Q_SLOTS:
    void connectToServer();

private slots:
    void sendRequest();
    void updateMessage();
    void error();
    void closeConnection();

private:
    QTcpSocket m_tcpSocket;
    quint16 m_nextBlockSize;
};

#endif // REQUEST_H
