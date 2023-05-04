
#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mySocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    connect(mySocket, &QTcpSocket::readyRead, this, &MainWindow::readReply);

    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::onBtnConnectClicked);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &MainWindow::onBtnDisconnectClicked);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::onLineEditReturnPressed);

    connect(mySocket, &QTcpSocket::disconnected, [this]() {
        this->writeLog("Disconnected from host");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnConnectClicked()
{
    mySocket->connectToHost(QHostAddress::LocalHost, 1234);

    if (mySocket->waitForConnected(3000)) {
        writeLog("[INFO] Connected to localhost:1234.");
    } else {
        writeLog("[FAIL] Connected to localhost:1234.");
    }
}

void MainWindow::onBtnDisconnectClicked()
{
    writeLog(QString("[INFO] Socket state: %1").arg(mySocket->state()));

    if (mySocket->isOpen()) {
        mySocket->close();

        writeLog("[INFO] Disonnected from localhost:1234.");
    }
}

void MainWindow::onLineEditReturnPressed()
{
    if (mySocket->state() != QAbstractSocket::ConnectedState) {
        writeLog("[WARN] Connection has not been established.");
        return;
    }

    char msg[1024];
    if (mySocket->isWritable()) {
        const QString qmsg = ui->lineEdit->text();

        memset(msg, '\0', sizeof(msg));
        memcpy(msg, qmsg.toUtf8(), qmsg.size() + 1);

        mySocket->write(msg);
        mySocket->waitForBytesWritten(1000);

        writeLog("Client send: " + qmsg);

        ui->lineEdit->clear();
    }
}

void MainWindow::readReply()
{
    const QByteArray ba = mySocket->readAll();

    writeLog(QString(ba));
}

void MainWindow::writeLog(const QString& log)
{
    ui->plainTextEdit->appendPlainText(log);
}
