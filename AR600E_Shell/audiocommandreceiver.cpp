#include "audiocommandreceiver.h"

AudioCommandReceiver::AudioCommandReceiver(QObject *parent)
{
    isRunning = false;
}

AudioCommandReceiver::~AudioCommandReceiver()
{
    exit();
}

void AudioCommandReceiver::run()
{
    m_udpSocketReceiver = new QUdpSocket;

    connect(m_udpSocketReceiver, SIGNAL(readyRead()), SLOT(processPendingDatagrams()), Qt::DirectConnection);

    if (!m_udpSocketReceiver->bind(mPort, QUdpSocket::ShareAddress))
    {
        qDebug()<< "ConsoleReceiver - Not Bind!";
    }

    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий

    disconnect(m_udpSocketReceiver, SIGNAL(readyRead()));
    m_udpSocketReceiver->close();


    /*while(isRunning)
    {

        sockaddr_in si_me;
        int slen;
        const int buffer_size  = 8;
        char buffer[buffer_size];

        if((m_udpSocketReceiver = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
        {
            qDebug()<<"ConsoleReceiver - Error creating socket";
            return;
        }

        si_me.sin_family = AF_INET;
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
        si_me.sin_port = htons(mPort);

        if(bind(m_udpSocketReceiver, (sockaddr*)&si_me, sizeof(si_me))==SOCKET_ERROR)
        {
            qDebug()<<"ConsoleReceiver - Not Bind!";
            return;
        }

        int recv_len;
        sockaddr_in si_other;
        slen=sizeof(si_other);
        memset(&si_other, 0, slen);


        if ((recv_len = recv(m_udpSocketReceiver, buffer, 1, 0) != SOCKET_ERROR))
        {
            qDebug() << "ConsoleReceiver data: " << QString::number(buffer[0]) << "size" << QString::number(recv_len) << endl;

            //разбор команд
            if(buffer[0] == 1)
                emit moveForward();
            else if(buffer[0] == 2)
                emit stopSolve();
            else if(buffer[0] == 3)
                emit stopMove();
        }
        else
        {
            DWORD err = WSAGetLastError();
            qDebug() << "Error: " << QString::number(err);
        }


        //Завершился цикл обработки событий

        closesocket(m_udpSocketReceiver);
    }*/
}


void AudioCommandReceiver::Connect()
{
    if(isRunning == false)
    {
        isRunning = true;
        start();
    }
}

void AudioCommandReceiver::Disconnect()
{
    if(isRunning == true)
    {
        isRunning = false;
        exit();
    }
}

void AudioCommandReceiver::processPendingDatagrams()
{
    while (m_udpSocketReceiver->hasPendingDatagrams())
    {
        //QByteArray datagram;
        //datagram.resize(m_udpSocketReceiver->pendingDatagramSize());
        //QHostAddress Host;
        //quint16 Port;

        char command = 0;
        int size = m_udpSocketReceiver->pendingDatagramSize();

        m_udpSocketReceiver->readDatagram(&command, 1);
        //m_udpSocketReceiver->readDatagram(datagram.data(), datagram.size(), &Host, &Port);
        //qDebug() << "ConsoleReceiver data: " << datagram.data() << "size" << QString::number(datagram.size()) << endl;
        qDebug() << "ConsoleReceiver data: " << QString::number(command) << "size" << QString::number(size) << endl;

        /*разбор команд
        if(datagram == "1")
            emit moveForward();
        else if(datagram == "2")
            emit stopSolve();
        else if(datagram == "3")
            emit stopMove();*/

        //разбор команд
        if(command == 1)
            emit moveForward();
        else if(command == 2)
            emit stopSolve();
        else if(command == 3)
            emit stopMove();

    }
}

