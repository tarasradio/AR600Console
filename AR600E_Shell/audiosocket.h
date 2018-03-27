#ifndef AUDIOSOCKET_H
#define AUDIOSOCKET_H

#include <QTcpSocket>
#include <QUdpSocket>

#define aPort 5004

class AudioSocket
{
public:
    AudioSocket();
    bool connect();
    void disconnect();	
    void playText(QString text);
    void playFile(QString filename);

private:
    //QTcpSocket* aserver;
    QUdpSocket* aserver;
    QHostAddress aHost; // = QHostAddress::LocalHost;
    QString aHostString = "192.169.1.200";
};

#endif // AUDIOSOCKET_H
