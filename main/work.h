#ifndef WORK_H
#define WORK_H

#include <QThread>
#include <QImage>
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include <QMovie>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QBoxLayout>

#include "mg56914.h"
#include "gpio.h"

#if defined(Q_OS_WIN32)
#define DEBUG_SERIAL_PORT   "COM33"
#else
#define DEBUG_SERIAL_PORT  "/dev/ttys0"
#endif

class WorkProcessThread : public QThread
{
    /*
     * 注意：必须添加Q_OBJECT宏使其能够应用Qt的信号槽机制，不然就没法更新UI界面啦
     */
    Q_OBJECT

public:
    WorkProcessThread(QThread *parent = 0);
    ~WorkProcessThread();
public:
    /*
     *继承QThread类之后，必须实现 run() 函数。在run函数中实现你要在子线程中运行的代码
     */
    virtual void run();

    bool OpenOBDSerialPort(QString OBDPort);
    bool OpenDebugSerialPort(QString DebugPort);
    void WriteDataToDebugSerialPort(QByteArray WriteData);
    void OpenIO(quint8 IO);
    void IOCtrl(quint8 IO, quint8 IONum, bool IOState);
    void IORead(quint8 IO, quint8 IONum, bool IOState);
    void IOWrite(quint8 IO, quint8 IONum, bool IOState);
    void UpdateOBDData(QByteArray obddata);
//signals:

private slots:
    void DebugSerialPortRxDataHandle();
    void Time1msHandle();

private:
   QSerialPort *OBDSerialPort;
   QSerialPort *BTSerialPort;
   QSerialPort *DebugSerialPort;
   QByteArray OBDUartData;

   QTimer *timer1ms;
   quint32 time1msCnt;
   qint8 time10msCnt;
   qint8 time50msCnt;
   qint8 time500msCnt;
   bool flag_1msTime;
   bool flag_5msTime;
   bool flag_10msTime;
   bool flag_50msTime;


};

#endif // MAINWIDGET_H
