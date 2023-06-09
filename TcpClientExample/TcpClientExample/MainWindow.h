
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void onBtnConnectClicked();
    void onBtnDisconnectClicked();
    void onLineEditReturnPressed();
    void readReply();

private:
    void writeLog(const QString& log);

private:
    Ui::MainWindow* ui;
    QTcpSocket* mySocket;
};

#endif // MAINWINDOW_H
