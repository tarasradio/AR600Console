#include "myTimer.h"

myTimer::myTimer(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
    m_delay = 5;
    curTime = 0;
    mState = STOPPED;
    timePointStop = 0;
    timePointStep = 0;
}

myTimer::~myTimer()
{

}

void myTimer::run()
{
    //нить потока создана
pointStart:
    isRestart = false;
    isRunning = true;

    m_timer = new QTimer;
    m_timer->setInterval(m_delay);
    connect(m_timer, SIGNAL(timeout()), SLOT(Count()), Qt::DirectConnection);
    m_timer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    m_timer->stop();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}

void myTimer::startCount()
{
    mState = RUNNING;
    if(!isRunning)
        start();
}

void myTimer::stopCount()
{
    curTime = 0;
    if(isRunning)
        exit();
}

void myTimer::setTimePointStop(long int timePoint)  //14c
{
    timePointStep = timePoint;
    timePointStop = timePointStep + 2500;
}

void myTimer::stopMove()
{
    mState = STOPPING;
}

void myTimer::startMove()
{
    mState = RUNNING;
}

void myTimer::Count()
{
    curTime += m_delay;

    /*if(curTime == timePointStop)
    {
        //curTime = 0;
        timePointStop += timePointStep;
        if(mState == STOPPING)
            stopMoveSignal();
    }*/
}

