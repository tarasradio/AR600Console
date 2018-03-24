#include "pultreceiver.h"

PultReceiver::PultReceiver(QObject *parent) : QObject(parent)
{
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

void PultReceiver::onReceivedData()
{
    QByteArray data;
    data.append(port.readAll());

    //TODO: добавить обработку сообщений, возможно с помощью
    // packetBuilder

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

