
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Request.h"
#include <QMainWindow>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected slots:
    void send();

private slots:
    void showMessage();

private:
    Ui::MainWindow* ui;
    QTcpServer* m_server;
    Request* m_request;
};

#endif // MAINWINDOW_H
