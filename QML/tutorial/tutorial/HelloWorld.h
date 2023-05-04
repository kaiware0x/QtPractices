
#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QDebug>
#include <QObject>
#include <QString>

class HelloWorld : public QObject {
    Q_OBJECT
public:
    explicit HelloWorld(QObject* parent = nullptr);

    // Q_INVOKABLEをつけるとQMLから呼び出しが可能になる
    Q_INVOKABLE void onButtonClicked() { qDebug() << "Hello, C++!"; }
};

#endif // HELLOWORLD_H
