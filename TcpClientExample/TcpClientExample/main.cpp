
#include "MainWindow.h"

#include <QApplication>

/// https://www.youtube.com/watch?v=mj92iVeuBS0

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
