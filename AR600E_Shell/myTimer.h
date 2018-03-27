#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#define STOP_PERIOD 25000

class myTimer : public QThread
{
    Q_OBJECT
public:
    explicit myTimer(QObject *parent = 0);
    ~myTimer();
    void run();
    void startCount();
    void stopCount();
    void setTimePointStop(long int timePoint);
    void stopMove();
    void startMove();

private:
    QTimer *m_timer;
    int m_delay;
    enum States { RUNNING, STOPPING, STOPPED } mState;
    bool isRunning;
    bool isRestart;
    bool isStopping;
    long int timePointStop, timePointStep;
    long int curTime;

signals:
    void stopMoveSignal();

public slots:
    void Count();
};

#endif // MYTIMER_H
