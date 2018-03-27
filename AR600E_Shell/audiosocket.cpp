#include "audiosocket.h"

AudioSocket::AudioSocket()
{

}

bool AudioSocket::connect()
{
    //aserver = new QTcpSocket();
    aHost = QHostAddress(aHostString);
    aserver = new QUdpSocket();
    aserver->connectToHost(aHost, aPort);
    if(aserver->waitForConnected(500))
        return true;
    return false;
}

void AudioSocket::disconnect()
{
    aserver->disconnectFromHost();
}

void AudioSocket::playText(QString text)
{
    //aserver->write((filename + "<EOF>").toUtf8());
    text.replace('\n', ' ');
    //int len = text.length();
    //aserver->write((char*)&len, sizeof(int));
    aserver->writeDatagram(text.toUtf8(), aHost, aPort);
}

void AudioSocket::playFile(QString filename)
{
    aserver->write((filename + "<EOF>").toUtf8());
}

