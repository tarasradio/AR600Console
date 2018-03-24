#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->paramCheckBox->setChecked(false);
    ui->parametersBox->setEnabled(false);
    ui->disconnectButton->setEnabled(false);
    ui->controlBox->setEnabled(false);

    ui->manStdCheckBox->setChecked(true);
    ui->stdMoves->setEnabled(false);
    //ui->accGroup->setEnabled(false);
    //ui->angAccGroup->setEnabled(false);
    ui->pauseSolveButton->setEnabled(false);
    ui->stopSolveButton->setEnabled(false);
    //ui->v1Button->setChecked(true);
    //ui->saveParamButton->setEnabled(false);

    mTimer = new myTimer();
    connect(mTimer, SIGNAL(stopMoveSignal()), this, SLOT(onTimerStopSignal()));

    mAudioSocket = new AudioSocket();

    initParams();
    initParamTable();

    on_refreshComsButton_clicked();
    connect(&pult, SIGNAL(dataReceived(QByteArray)), this, SLOT(on_pult_dataReceived(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initParams()
{
    acc = 0; angAcc = 0;
    vmax = 0.010;
    statePlay = 0;
    hs = 0.1; h = 0.2; ts = 5.0;
    /*cx = -0.00002; cy = 0.00002; cx1 = 0.00002; cy1 = -0.00002;
    cux = 0.00005; cuy = -0.000025; cux1 = 0.00005; cuy1 = 0.00002;
    tdin = 0.4; tdin2 = 0.4;
    dx = 0; dy = 0; dx1 = 0; dy1 = 0;
    duxm = 0; duym = 0; duxm1 = 0; duym1 = 0;
    PGate = 1200; IGate = 1;*/

    cx = 0; cy = 0; cx1 = 0; cy1 = 0;
    cux = 0; cuy = 0; cux1 = 0; cuy1 = 0;
    tdin = 0; tdin2 = 0;
    dx = 0; dy = 0; dx1 = 0; dy1 = 0;
    duxm = 0; duym = 0; duxm1 = 0; duym1 = 0;
    ui->hsBox->setValue(hs); ui->hBox->setValue(h); ui->tsBox->setValue(ts);
    ui->cxBox->setValue(cx); ui->cyBox->setValue(cy); ui->cx1Box->setValue(cx1); ui->cy1Box->setValue(cy1);
    ui->cuxBox->setValue(cux); ui->cuyBox->setValue(cuy); ui->cux1Box->setValue(cux1); ui->cuy1Box->setValue(cuy1);
    ui->tdinBox->setValue(tdin); ui->tdin2Box->setValue(tdin2);
    ui->dxBox->setValue(dx); ui->dyBox->setValue(dy); ui->dx1Box->setValue(dx1); ui->dy1Box->setValue(dy1);
    ui->duxmBox->setValue(duxm); ui->duymBox->setValue(duym); ui->duxm1Box->setValue(duxm1); ui->duym1Box->setValue(duym1);

    ui->cxBox->setToolTip("cx - коэффициент обратной связи по продольному смещению центра масс относительно левой ноги в фазе опоры	+-0.00004	номинальное значение -0.00002");
    ui->cyBox->setToolTip("cy - коэффициент обратной связи по поперечному смещению центра масс относительно левой ноги в фазе опоры	+-0.00008	номинальное значение +0.00002");
    ui->cx1Box->setToolTip("cx1 - коэффициент обратной связи по продольному смещению центра масс относительно правой ноги в фазе опоры	+-0.00004	номинальное значение +0.00002");
    ui->cy1Box->setToolTip("cy1 - коэффициент обратной связи по поперечному смещению центра масс относительно правой ноги в фазе опоры	+-0.00008	номинальное значение -0.00002");
    ui->cuxBox->setToolTip("cux - коэффициент обратной связи по поперечной реакции левой стопы, влияет (изменяет) продольный угол стопы	+-0.00005	номинальное значение +0.00005");
    ui->cuyBox->setToolTip("cuy - коэффициент обратной связи по продольной реакции левой стопы, влияет (изменяет) продольный угол стопы	+-0.00003	номинальное значение -0.000025");
    ui->cux1Box->setToolTip("cux1 - коэффициент обратной связи по поперечной реакции правой стопы, влияет (изменяет) продольный угол стопы	+-0.00012	номинальное значение +0.00005");
    ui->cuy1Box->setToolTip("cuy1 - коэффициент обратной связи по продольной реакции правой стопы, влияет (изменяет) продольный угол стопы	+-0.00008	номинальное значение +0.00002");
    ui->tdinBox->setToolTip("tdin - опережение-задержка времени начала переноса центра масс с одной ноги на другую (левая нога)		0 - 10-20% от периода шага	номинальное 0.4");
    ui->tdin2Box->setToolTip("tdin2 - опережение-задержка времени начала переноса центра масс с одной ноги на другую (правая нога)		0 - 10-20% от периода шага	номинальное 0.4");
    ui->dxBox->setToolTip("dx - постоянное продольное смещение центра масс относительно левой стопы в  фазе опоры				+-0.01	номинальное значение 0");
    ui->dyBox->setToolTip("dy - постоянное поперечное смещение центра масс относительно левой стопы в  фазе опоры				+-0.01	номинальное значение 0");
    ui->dx1Box->setToolTip("dx1 - постоянное продольное смещение центра масс относительно правой стопы в  фазе опоры			+-0.01	номинальное значение 0");
    ui->dy1Box->setToolTip("dy1 - постоянное продольное смещение центра масс относительно правой стопы в  фазе опоры			+-0.01	номинальное значение 0");
    ui->duxmBox->setToolTip("duxm - коэффициент обратной связи по продольному углу левой стопы контура обратной связи по реактивному моменту		0 - 1");
    ui->duymBox->setToolTip("duym - коэффициент обратной связи по поперечному углу левой стопы контура обратной связи по реактивному моменту		0 - 1");
    ui->duxm1Box->setToolTip("duxm1 - коэффициент обратной связи по продольному углу правой стопы контура обратной связи по реактивному моменту	0 - 1");
    ui->duym1Box->setToolTip("duym1 - коэффициент обратной связи по поперечному углу правой стопы контура обратной связи по реактивному моменту	0 - 1");

}

void MainWindow::writeToFile()
{
    QString control;
    control += QString::number(acc,'f',4) + " " + QString::number(vmax, 'f', 3); // + " " + QString::number(angAcc,'g',4);
    control += " " + QString::number(statePlay) + " 1";
    control += "\r\n" + QString::number(hs,'f',2) + "\r\n" + QString::number(h,'f',2) + "\r\n" + QString::number(ts,'f',2);
    control += "\r\n" + QString::number(cx,'f',6) + "\r\n" + QString::number(cy,'f',6) + "\r\n" + QString::number(cx1,'f',6) + "\r\n" + QString::number(cy1,'f',6);
    control += "\r\n" + QString::number(cux,'f',6) + "\r\n" + QString::number(cuy,'f',6) + "\r\n" + QString::number(cux1,'f',6) + "\r\n" + QString::number(cuy1,'f',6);
    control += "\r\n" + QString::number(tdin,'f',2) + "\r\n" + QString::number(tdin2,'f',2);
    control += "\r\n" + QString::number(dx,'f',6) + "\r\n" + QString::number(dy,'f',6) + "\r\n" + QString::number(dx1,'f',6) + "\r\n" + QString::number(dy1,'f',6);
    control += "\r\n" + QString::number(duxm,'f',6) + "\r\n" + QString::number(duym,'f',6) + "\r\n" + QString::number(duxm1,'f',6) + "\r\n" + QString::number(duym1,'f',6);

    command[0] = '0';
    sender->writeDatagram(command, 1, mHost, mPort);

    QByteArray packet = control.toUtf8();
    sender->writeDatagram(packet, mHost, mPort);
}

void MainWindow::resetControl()
{
    if(ui->accelSlider->value() == 60)
        writeToFile();
    else
        ui->accelSlider->setValue(60);
}

void MainWindow::initParamTable()
{
    ui->tableWidget->setColumnWidth(0, 200);

    ui->tableWidget->setColumnWidth(1, 50);
    ui->tableWidget->setColumnWidth(2, 50);
    ui->tableWidget->setColumnWidth(3, 50);

    // все строки высотой 21px
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->setRowHeight(row, 21);

    // вставляем ячейки со значениями
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *itemValue = new QTableWidgetItem;
        itemValue->setText("0.00");
        itemValue->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,1,itemValue);
    }

    // вставляем ячейки со значениями
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *itemValue = new QTableWidgetItem;
        itemValue->setText("Параметр");
        itemValue->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,0,itemValue);
    }
}

void MainWindow::on_paramCheckBox_clicked(bool checked)
{
    ui->parametersBox->setEnabled(!checked);
    if(checked)
    {
        if(ui->paramSlider->value() != 10)
            ui->paramSlider->setValue(10);
        else
        {
        //hs = 0.1; h = 0.2; ts = 5.0;
            cx = -0.00002; cy = 0.00002; cx1 = 0.00002; cy1 = -0.00002;
            cux = 0.00005; cuy = -0.000025; cux1 = 0.00005; cuy1 = 0.00002;
            tdin = 0.4; tdin2 = 0.4;
            dx = 0; dy = 0; dx1 = 0; dy1 = 0;
            duxm = 0; duym = 0; duxm1 = 0; duym1 = 0;
            PGate = 1200;
            IGate = 1;
            //записать в файл параметры по умолчанию
            writeToFile();

            ui->hsBox->setValue(hs); ui->hBox->setValue(h); ui->tsBox->setValue(ts);

            ui->cxBox->setValue(cx); ui->cyBox->setValue(cy); ui->cx1Box->setValue(cx1); ui->cy1Box->setValue(cy1);
            ui->cuxBox->setValue(cux); ui->cuyBox->setValue(cuy); ui->cux1Box->setValue(cux1); ui->cuy1Box->setValue(cuy1);
            ui->tdinBox->setValue(tdin); ui->tdin2Box->setValue(tdin2);
            ui->dxBox->setValue(dx); ui->dyBox->setValue(dy); ui->dx1Box->setValue(dx1); ui->dy1Box->setValue(dy1);
            ui->duxmBox->setValue(duxm); ui->duymBox->setValue(duym); ui->duxm1Box->setValue(duxm1); ui->duym1Box->setValue(duym1);
        }
    }
}

void MainWindow::on_accelSlider_valueChanged(int value)
{
    if(value == 50)
        acc = 0;
    else
        //acc = 0.0002 * value - 0.01;
        acc = 0.1 * value - 5;
    ui->accelBox->setValue(acc);
    //записать в файл
    writeToFile();
    mTimer->startMove();
}

void MainWindow::on_stopButton_clicked()
{
    mTimer->stopMove();
    /*if(ui->accelSlider->value() == 50)
        writeToFile();
    else
        ui->accelSlider->setValue(50);*/
}

void MainWindow::on_angAccelSlider_valueChanged(int value)
{
    if(value == 50)
        angAcc = 0;
    else
        angAcc = 0.0002 * value - 0.01;
    ui->angAccelBox->setValue(angAcc);
    //записать в файл
    writeToFile();
}

void MainWindow::on_angStopButton_clicked()
{
    ui->angAccelSlider->setValue(50);
}

void MainWindow::on_saveParamButton_clicked()
{
    //записать параметры в файл
    hs = ui->hsBox->value();
    h = ui->hBox->value();
    ts = ui->tsBox->value();

    cx = ui->cxBox->value();
    cy = ui->cyBox->value();
    cx1 = ui->cx1Box->value();
    cy1 = ui->cy1Box->value();
    cux = ui->cuxBox->value();
    cuy = ui->cuyBox->value();
    cux1 = ui->cux1Box->value();
    cuy1 = ui->cuy1Box->value();
    tdin = ui->tdinBox->value();
    tdin2 = ui->tdin2Box->value();
    dx = ui->dxBox->value();
    dy = ui->dyBox->value();
    dx1 = ui->dx1Box->value();
    dy1 = ui->dy1Box->value();
    duxm = ui->duxmBox->value();
    duym = ui->duymBox->value();
    duxm1 = ui->duxm1Box->value();
    duym1 = ui->duym1Box->value();

    PGate = ui->KBox->value();
    IGate = ui->IBox->value();
    writeToFile();
}

void MainWindow::on_connectButton_clicked() //TODO
{
    //try connect
    sender = new QUdpSocket(this);
    sender->connectToHost(mHost, mPort);
    if(sender->waitForConnected(1000))
    {
        command[0] = 'B';
        //writeToFile();
        ui->controlBox->setEnabled(true);
        ui->disconnectButton->setEnabled(true);
        ui->connectButton->setEnabled(false);
    }

    if(mAudioSocket->connect())
        ui->audioGroupBox->setEnabled(true);
    else
        ui->audioGroupBox->setEnabled(false);
}

void MainWindow::on_disconnectButton_clicked() // TODO
{
    //disconnect
    on_stopButton_clicked();
    //command[0] = 'C';
    //sender->writeDatagram(command, 1, mHost, mPort);
    //if(ui->runSolveButton->isEnabled())
        //on_stopSolveButton_clicked();

    sender->disconnectFromHost();
    sender->close();

    ui->controlBox->setEnabled(false);
    ui->disconnectButton->setEnabled(false);
    ui->connectButton->setEnabled(true);

    mAudioSocket->disconnect();
    ui->audioGroupBox->setEnabled(false);
}

void MainWindow::on_forwardButton_clicked()
{
    command[0] = '3';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_backButton_clicked()
{
    command[0] = '4';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_stopAllButton_clicked()
{
    command[0] = '5';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_leftButton_clicked()
{
    command[0] = '6';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_rightButton_clicked()
{
    command[0] = '7';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_startButton_clicked()
{
    command[0] = '8';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_runSolveButton_clicked()
{
    //acc = 1;
    statePlay = 0;
    resetControl();

    ui->accGroup->setEnabled(true);
    ui->angAccGroup->setEnabled(true);
    ui->stopSolveButton->setEnabled(true);
    ui->runSolveButton->setEnabled(false);
    ui->pauseSolveButton->setEnabled(true);

    writeToFile();
    command[0] = '1';
    sender->writeDatagram(command, 1, mHost, mPort);

    mTimer->setTimePointStop(25000);
    mTimer->startCount();
}

void MainWindow::on_stopSolveButton_clicked()
{
    ui->accGroup->setEnabled(false);
    ui->angAccGroup->setEnabled(false);
    ui->stopSolveButton->setEnabled(false);
    ui->runSolveButton->setEnabled(true);
    ui->pauseSolveButton->setEnabled(false);

    statePlay = 2;
    writeToFile();
    command[0] = '2';
    sender->writeDatagram(command, 1, mHost, mPort);
    Sleep(500);
    statePlay = 0;
    writeToFile();

    mTimer->stopCount();
}

void MainWindow::on_manStdCheckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->manMoves->setEnabled(true);
        ui->stdMoves->setEnabled(false);
        command[0] = '9';
    }
    else
    {
        ui->manMoves->setEnabled(false);
        ui->stdMoves->setEnabled(true);
        command[0] = 'A';
        on_stopSolveButton_clicked();
    }
    //sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_v1Button_clicked()
{
    vmax = 0.005; //0.017;
    ui->v2Button->setChecked(false);
    ui->v3Button->setChecked(false);
    writeToFile();
}

void MainWindow::on_v2Button_clicked()
{
    vmax = 0.010; // 0.024;
    ui->v1Button->setChecked(false);
    ui->v3Button->setChecked(false);
    writeToFile();
}

void MainWindow::on_v3Button_clicked()
{
    vmax = 0.020; //0.034;
    ui->v1Button->setChecked(false);
    ui->v2Button->setChecked(false);
    writeToFile();
}

void MainWindow::on_vSetButton_clicked()
{
    vmax = ui->vBox->value();
    ui->v1Button->setChecked(false);
    ui->v2Button->setChecked(false);
    ui->v3Button->setChecked(false);
    writeToFile();
}

void MainWindow::onTimerStopSignal()
{
    if(ui->accelSlider->value() == 50)
            writeToFile();
        else
            ui->accelSlider->setValue(50);
}

void MainWindow::on_rebootButton_clicked()
{
    command[0] = '3';
    sender->writeDatagram(command, 1, mHost, mPort);
}

void MainWindow::on_hsBox_valueChanged(double arg1)
{
    hs = arg1;
    //writeToFile();
}

void MainWindow::on_hBox_valueChanged(double arg1)
{
    h = arg1;
    //writeToFile();
}

void MainWindow::on_tsBox_valueChanged(double arg1)
{
    ts = arg1;
    //writeToFile();
}

void MainWindow::on_cxBox_valueChanged(double arg1)
{
    cx = arg1;
    //writeToFile();
}

void MainWindow::on_cyBox_valueChanged(double arg1)
{
    cy = arg1;
    //writeToFile();
}

void MainWindow::on_cx1Box_valueChanged(double arg1)
{
    cx1 = arg1;
    //writeToFile();
}

void MainWindow::on_cy1Box_valueChanged(double arg1)
{
    cy1 = arg1;
    //writeToFile();
}

void MainWindow::on_cuxBox_valueChanged(double arg1)
{
    cux = arg1;
    //writeToFile();
}

void MainWindow::on_cuyBox_valueChanged(double arg1)
{
    cuy = arg1;
    //writeToFile();
}

void MainWindow::on_cux1Box_valueChanged(double arg1)
{
    cux1 = arg1;
    //writeToFile();
}

void MainWindow::on_cuy1Box_valueChanged(double arg1)
{
    cuy1 = arg1;
    //writeToFile();
}

void MainWindow::on_tdinBox_valueChanged(double arg1)
{
    tdin = arg1;
    //writeToFile();
}

void MainWindow::on_tdin2Box_valueChanged(double arg1)
{
    tdin2 = arg1;
    //writeToFile();
}

void MainWindow::on_dxBox_valueChanged(double arg1)
{
    dx = arg1;
    //writeToFile();
}

void MainWindow::on_dyBox_valueChanged(double arg1)
{
    dy = arg1;
    //writeToFile();
}

void MainWindow::on_dx1Box_valueChanged(double arg1)
{
    dx1 = arg1;
    //writeToFile();
}

void MainWindow::on_dy1Box_valueChanged(double arg1)
{
    dy1 = arg1;
    //writeToFile();
}

void MainWindow::on_pauseSolveButton_clicked()
{
    if(statePlay == 0)
        statePlay = 1;
    else
        statePlay = 0;
    writeToFile();
}

void MainWindow::on_resetParamsButton_clicked()
{
    /*if(ui->paramSlider->value() != 0)
        ui->paramSlider->setValue(0);
    else
    {*/
        //writeToFile();

        //hs = 0; h = 0; ts = 0;
        cx = 0; cy = 0; cx1 = 0; cy1 = 0;
        cux = 0; cuy = 0; cux1 = 0; cuy1 = 0;
        tdin = 0; tdin2 = 0;
        dx = 0; dy = 0; dx1 = 0; dy1 = 0;
        duxm = 0; duym = 0; duxm1 = 0; duym1 = 0;
        ui->hsBox->setValue(hs); ui->hBox->setValue(h); ui->tsBox->setValue(ts);
        ui->cxBox->setValue(cx); ui->cyBox->setValue(cy); ui->cx1Box->setValue(cx1); ui->cy1Box->setValue(cy1);
        ui->cuxBox->setValue(cux); ui->cuyBox->setValue(cuy); ui->cux1Box->setValue(cux1); ui->cuy1Box->setValue(cuy1);
        ui->tdinBox->setValue(tdin); ui->tdin2Box->setValue(tdin2);
        ui->dxBox->setValue(dx); ui->dyBox->setValue(dy); ui->dx1Box->setValue(dx1); ui->dy1Box->setValue(dy1);
        ui->duxmBox->setValue(duxm); ui->duymBox->setValue(duym); ui->duxm1Box->setValue(duxm1); ui->duym1Box->setValue(duym1);
        writeToFile();
    //}

}

void MainWindow::on_paramSlider_valueChanged(int value)
{
    double k = (float)value/10;
    /*cx = cx*k; cy = cy*k; cx1 = cx1*k; cy1 = cy1*k;
    cux = cux*k; cuy = cuy*k; cux1 = cux1*k; cuy1 = cuy1*k;
    tdin = tdin*k; tdin2 = tdin2*k;
    dx = dx*k; dy = dy*k; dx1 = dx1*k; dy1 = dy1*k;*/
    cx = -0.00002*k; cy = 0.00002*k; cx1 = 0.00002*k; cy1 = -0.00002*k;
    cux = 0.00005*k; cuy = -0.000025*k; cux1 = 0.00005*k; cuy1 = 0.00002*k;
    tdin = 0.4*k; tdin2 = 0.4*k;
    dx = 0*k; dy = 0*k; dx1 = 0*k; dy1 = 0*k;
    duxm = 0*k; duym = 0*k; duxm1 = 0*k; duym1 = 0*k;

    ui->hsBox->setValue(hs); ui->hBox->setValue(h); ui->tsBox->setValue(ts);
    ui->cxBox->setValue(cx); ui->cyBox->setValue(cy); ui->cx1Box->setValue(cx1); ui->cy1Box->setValue(cy1);
    ui->cuxBox->setValue(cux); ui->cuyBox->setValue(cuy); ui->cux1Box->setValue(cux1); ui->cuy1Box->setValue(cuy1);
    ui->tdinBox->setValue(tdin); ui->tdin2Box->setValue(tdin2);
    ui->dxBox->setValue(dx); ui->dyBox->setValue(dy); ui->dx1Box->setValue(dx1); ui->dy1Box->setValue(dy1);
    ui->duxmBox->setValue(duxm); ui->duymBox->setValue(duym); ui->duxm1Box->setValue(duxm1); ui->duym1Box->setValue(duym1);

    writeToFile();
}

void MainWindow::on_playAudioButton_clicked()
{
    mAudioSocket->playFile(ui->audiofileInput->text());
}

void MainWindow::on_refreshComsButton_clicked()
{
    ui->comsComboBox->clear();
    ui->comsComboBox->addItems(pult.GetComPortsList());
}

void MainWindow::on_connectPultButton_clicked()
{
    if(pult.OpenPort(ui->comsComboBox->currentText()))
        ui->pultStatusLabel->setText("Пульт подключен");
    else
        ui->pultStatusLabel->setText("Пульт не подключен");
}

void MainWindow::on_disconnectPultButton_clicked()
{
    pult.ClosePort();
    ui->pultStatusLabel->setText("Пульт не подключен");
}

void MainWindow::on_pult_dataReceived(QByteArray data)
{
    ui->pultDataEdit->setText(data);
}
