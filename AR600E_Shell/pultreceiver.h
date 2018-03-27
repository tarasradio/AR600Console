#ifndef PULTRECEIVER_H
#define PULTRECEIVER_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QString>

class PultReceiver : public QObject
{
    Q_OBJECT

public:
    explicit PultReceiver(QObject *parent = 0);
    ~PultReceiver();
    QStringList GetComPortsList();
    bool OpenPort(QString portName);
    void ClosePort();

private:
    QSerialPort port;

    void initPort();
    unsigned short* processPultData(QByteArray pultData);

private slots:
    void onReceivedData();

signals:
    void dataReceived(QByteArray data);
};

#endif // PULTRECEIVER_H
