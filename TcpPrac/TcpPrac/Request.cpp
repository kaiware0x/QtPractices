
#include "Request.h"

Request::Request(QObject* parent)
    : QObject(parent)
{
    /// 接続
    connect(&m_tcpSocket, &QTcpSocket::connected, this, &Request::sendRequest);

    /// 接続終了
    connect(&m_tcpSocket, &QTcpSocket::disconnected, this, &Request::closeConnection);

    /// 受信中
    connect(&m_tcpSocket, &QTcpSocket::readyRead, this, &Request::updateMessage);

    /// エラー検出
    connect(&m_tcpSocket, &QTcpSocket::errorOccurred, this, &Request::error);
}

/**
 * @brief 接続開始
 */
void Request::connectToServer()
{
    /// LocalHostの6178ポートに接続
    m_tcpSocket.connectToHost(QHostAddress::LocalHost, 6178);
    m_nextBlockSize = 0;
}

/**
 * @brief データを作成して送信
 */
void Request::sendRequest()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_1);

    QString string = "Request";
    out << quint16(string.size()) << string;

    m_tcpSocket.write(block);
}

/**
 * @brief Request::updateMessage
 */
void Request::updateMessage()
{
    QDataStream in(&m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_1);

    forever
    {
        /// 次に読み出すブロックサイズの取得
        if (m_nextBlockSize == 0) {
            if (m_tcpSocket.bytesAvailable() < sizeof(quint16))
                break;
            in >> m_nextBlockSize;
        }

        /// データをすべて受信したか？
        if (m_nextBlockSize == 0xFFFF) {
            m_tcpSocket.close();
            break;
        }

        /// データが足りていない場合は強制Break
        if (m_tcpSocket.bytesAvailable() < m_nextBlockSize)
            break;

        in >> message;

        m_nextBlockSize = 0;
    }
}

/**
 * @brief Socketを閉じる
 */
void Request::closeConnection()
{
    m_tcpSocket.close();

    /// 送受信終了シグナル
    emit done();
}

void Request::error()
{
    message = m_tcpSocket.errorString();
    m_tcpSocket.close();
    emit done();
}
