
#ifndef MYTASK_H
#define MYTASK_H

#include <QRunnable>

class MyTask : public QRunnable {
public:
    MyTask(const qintptr& socketDescriptor);

    void run();

private:
    const qintptr mySocketDescriptor;
};

#endif // MYTASK_H
