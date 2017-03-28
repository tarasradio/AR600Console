#ifndef AUDIOSOCKET_H
#define AUDIOSOCKET_H

#include <QTcpSocket>
#include <QUdpSocket>

#define aPort 54321

class AudioSocket
{
public:
    AudioSocket();
    bool connect();
    void disconnect();
    void playFile(QString filename);

private:
    QTcpSocket* aserver;
    QHostAddress aHost = QHostAddress::LocalHost; //"192.169.1.201"
};

#endif // AUDIOSOCKET_H
