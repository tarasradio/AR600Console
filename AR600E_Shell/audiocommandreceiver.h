#ifndef AUDIOCOMMANDRECEIVER_H
#define AUDIOCOMMANDRECEIVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QDebug>
//#include <winsock2.h>
//#include <windows.h>

class AudioCommandReceiver : public QThread
{
    Q_OBJECT
public:
    explicit AudioCommandReceiver(QObject *parent = 0);
    ~AudioCommandReceiver();

    void Connect();
    void Disconnect();

signals:
    void ReadyData();
    void moveForward();
    void stopSolve();
    void stopMove();

protected:
    void run();

private:
    //private variable
    QUdpSocket *m_udpSocketReceiver;
    //SOCKET m_udpSocketReceiver;

    volatile bool isRunning;
    QHostAddress mHost; //= QHostAddress::LocalHost;
    int mPort = 5005;

private slots:
    void processPendingDatagrams();
};

#endif // AUDIOCOMMANDRECEIVER_H
