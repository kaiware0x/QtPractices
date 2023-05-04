
#include "MyTask.h"

#include <QByteArray>
#include <QTcpSocket>

MyTask::MyTask(const qintptr& socketDescriptor)
    : QRunnable()
    , mySocketDescriptor(socketDescriptor)
{
    setAutoDelete(true);
}

void MyTask::run()
{
    if (!mySocketDescriptor) {
        return;
    }

    /// # socket descriptorとは
    /// ソケットのIDのようなもの。
    /// 共通のDescriptorを持つソケット同士が通信できる。

    QTcpSocket socket;
    socket.setSocketDescriptor(mySocketDescriptor);
    if (!socket.isOpen()) {
        return;
    }

    socket.write("Hello client, I'm server.");

    /// ソケットへデータを書き出す。bytesWrittenシグナルがEmitされる。
    /// クライアント側のソケットではreadyReadシグナルがEmitされる。
    socket.waitForBytesWritten();
    socket.flush(); /// 内部のバッファをすべて書き出す

    /// ソケットにデータが書き込まれるのを待つ。デフォルト30秒間待ち受け。
    /// 新しいデータが来ていた場合タイマーはリセットされる。
    while (socket.waitForReadyRead()) {
        QByteArray inBuff = socket.readAll();
        qInfo() << mySocketDescriptor << ":" << inBuff;

        /// quit という文字列が来たらbreak
        if (!strncmp(inBuff, "quit", 4)) {
            qInfo() << mySocketDescriptor << ": Quit";
            break;
        }

        socket.write("Server reply: ");
        socket.write(inBuff);
        socket.waitForBytesWritten();
        socket.flush();
    }

    qInfo() << mySocketDescriptor << ": Close";
    socket.close();
}
