#include "pultreceiver.h"

PultReceiver::PultReceiver(QObject *parent) : QObject(parent)
{
    initPort();
    connect(&port, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

PultReceiver::~PultReceiver()
{
}

QStringList PultReceiver::GetComPortsList()
{
    QSerialPortInfo info;
    QList<QSerialPortInfo> ports = info.availablePorts();
    QStringList list;
    for(int i = 0; i < ports.size(); i++)
        list.append(ports[i].portName());
    return list;
}

void PultReceiver::initPort()
{
    port.setBaudRate(QSerialPort::Baud115200);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);
}

unsigned short* PultReceiver::processPultData(QByteArray pultData)
{
    //TODO: переписать по нормальному, добавить перевод в скорости
    // для выставления на GUI и отправки фрунду

    int dataSize = pultData.size();
    char *data = pultData.data();
    unsigned short results[6] = { 0 };
    unsigned short velocityX, velocityY;
    if(dataSize == 32)
    {
        if(data[0] == 0x20 && data[1] == 0x40)
        {
            velocityX = *((unsigned short*)(data + 2));
            velocityY = *((unsigned short*)(data + 2));
            memcpy(results, data + 2, 4);
        }
    }

    //TODO: добавить packetBuilder и сигнал по окончанию приема пакета

    return results;
}

void PultReceiver::onReceivedData()
{
    QByteArray data;
    data.append(port.readAll());

    //TODO: добавить обработку сообщений, возможно с помощью
    // packetBuilder
    //unsigned short *pultData = processPultData(data);

    dataReceived(data);
}

bool PultReceiver::OpenPort(QString portName)
{
    if(port.isOpen())
        ClosePort();
    port.setPortName(portName);
    initPort();
    return port.open(QIODevice::ReadOnly);
}

void PultReceiver::ClosePort()
{
    //TODO: добавить сигналирование главному окну
    port.close();
}

