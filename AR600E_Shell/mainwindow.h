#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QUdpSocket>
#include <QFileDialog>
#include <windows.h>
#include "myTimer.h"
#include "audiosocket.h"
#include "audiocommandreceiver.h"
#include "pultreceiver.h"

#define mHost QHostAddress::LocalHost
#define mPort 55555

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    

private:
    Ui::MainWindow *ui;
    double acc, angAcc;
    double vmax;
    int statePlay;
    double hs, h, ts;
    double cx, cy, cx1, cy1, cux, cuy, cux1, cuy1;
    double tdin, tdin2, dx, dy, dx1, dy1;
    double duxm, duym, duxm1, duym1;
    int PGate, IGate;
    void writeToFile();
    QUdpSocket* sender;
    char command[1];
    void resetControl();
    void initParams();
    void initParamTable();
    myTimer *mTimer;

    AudioSocket* mAudioSocket;
    AudioCommandReceiver* mAudioCommandReceiver;

    PultReceiver pult;

private slots:
    void on_paramCheckBox_clicked(bool checked);
    void on_accelSlider_valueChanged(int value);
    void on_stopButton_clicked();
    void on_saveParamButton_clicked();
    void on_angAccelSlider_valueChanged(int value);
    void on_angStopButton_clicked();
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_manStdCheckBox_clicked(bool checked);
    void on_forwardButton_clicked();
    void on_backButton_clicked();
    void on_stopAllButton_clicked();
    void on_leftButton_clicked();
    void on_rightButton_clicked();
    void on_startButton_clicked();
    void on_runSolveButton_clicked();
    void on_stopSolveButton_clicked();
    void on_v1Button_clicked();
    void on_v2Button_clicked();
    void on_v3Button_clicked();
    void on_rebootButton_clicked();
    void on_hsBox_valueChanged(double arg1);
    void on_hBox_valueChanged(double arg1);
    void on_tsBox_valueChanged(double arg1);
    void on_cxBox_valueChanged(double arg1);
    void on_cyBox_valueChanged(double arg1);
    void on_cx1Box_valueChanged(double arg1);
    void on_cy1Box_valueChanged(double arg1);
    void on_cuxBox_valueChanged(double arg1);
    void on_cuyBox_valueChanged(double arg1);
    void on_cux1Box_valueChanged(double arg1);
    void on_cuy1Box_valueChanged(double arg1);
    void on_tdinBox_valueChanged(double arg1);
    void on_tdin2Box_valueChanged(double arg1);
    void on_dxBox_valueChanged(double arg1);
    void on_dyBox_valueChanged(double arg1);
    void on_dx1Box_valueChanged(double arg1);
    void on_dy1Box_valueChanged(double arg1);
    void on_pauseSolveButton_clicked();
    void on_resetParamsButton_clicked();
    void on_paramSlider_valueChanged(int value);
    void on_vSetButton_clicked();

    void onTimerStopSignal();
    void on_playAudioButton_clicked();
    void on_playFileButton_clicked();
    void onStopAudioCommand_received();

    void on_refreshComsButton_clicked();
    void on_connectPultButton_clicked();
    void on_disconnectPultButton_clicked();
    void pultPortClosed();
    void pultDataReceived(QByteArray data);
    void pultPacketReceived(QList<short> packet);
};


#endif // MAINWINDOW_H
