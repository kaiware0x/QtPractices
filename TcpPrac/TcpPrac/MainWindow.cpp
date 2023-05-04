
#include "MainWindow.h"
#include "Request.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(new QTcpServer(this))
    , m_request(new Request)
{
    ui->setupUi(this);

    m_server->listen(QHostAddress::Any, 6178);

    connect(m_server, &QTcpServer::newConnection, this, &MainWindow::send);
    connect(ui->pushButton, &QPushButton::clicked, m_request, &Request::connectToServer);
    connect(m_request, &Request::done, this, &MainWindow::showMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send()
{
    QTcpSocket* client = m_server->nextPendingConnection();
    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);

    QDataStream out(client);
    out.setVersion(QDataStream::Qt_4_1);

    QString string = "Send";
    out << quint16(string.size()) << string << quint16(0xFFFF);
}

void MainWindow::showMessage()
{
    QMessageBox msgBox(this);
    msgBox.setText(m_request->message);
    msgBox.exec();
}
