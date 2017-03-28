#include "audiosocket.h"

AudioSocket::AudioSocket()
{

}

bool AudioSocket::connect()
{
    aserver = new QTcpSocket();
    aserver->connectToHost(aHost, aPort);
    if(aserver->waitForConnected(10000))
        return true;
    return false;
}

void AudioSocket::disconnect()
{
    aserver->disconnectFromHost();
}

void AudioSocket::playFile(QString filename)
{
    aserver->write((filename + "<EOF>").toUtf8());
}

