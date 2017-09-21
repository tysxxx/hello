
#include "work.h"
#include <QDebug>
#include <QTime>


/*
 *数据初始化
 */
WorkProcessThread::WorkProcessThread(QThread *parent):QThread(parent)
{   //                        1    2    3    4     5    6    7     8    9    10     11    12   13 14 15
    QByteArray tmp("$OBD-RT,11.4,15276,172,91.37,21.17,215,36.13,36.13,67.28, 195, 24.31,85.33,0, 1, 0\r\n");

    qDebug() << tmp.count(',');

    if(tmp.endsWith("\r\n") == true)
    {
        qint8 buf[15] = {0};
        QString str(tmp);
        for(qint8 i = 0, j = 0; i < str.length(); i++)
        {
            if(str.at(i) == ',')
            {
                buf[j] = i;
                j++;
            }
        }

        bool ok;

        qDebug() << "voltage = " << str.mid(buf[0]+1, buf[1]-buf[0]-1).toFloat(&ok);
        qDebug() << "engine speed = " << str.mid(buf[1]+1, buf[2]-buf[1]-1).toLong(&ok, 10);
        qDebug() << "runnig speed = " << str.mid(buf[2]+1, buf[3]-buf[2]-1).toLong(&ok, 10);
        qDebug() << "cur mileage = " << str.mid(buf[8]+1, buf[9]-buf[8]-1).toFloat(&ok);
        qDebug() << "sum mileage = " << str.mid(buf[9]+1, buf[10]-buf[9]-1).toLong(&ok, 10);
        if(ok == true)
        {
          qDebug() << "success";
        }
    }


   //QString str="hello world ttt";
   //QVector<QString>::iterator iterator;


    QString str = "hello";

    OBDUartData.clear();
    OpenDebugSerialPort(DEBUG_SERIAL_PORT);

//    flag_1msTime = false;
//    timer1ms = new QTimer();
//    connect(timer1ms, SIGNAL(timeout()), this, SLOT(Time1msHandle()));
//    timer1ms->start(1);


}

/*
 * 析构函数
 */
WorkProcessThread::~WorkProcessThread()
{

}

/*
 * 打开调试串口
 */
bool WorkProcessThread::OpenDebugSerialPort(QString DebugPortName)
{
    DebugSerialPort = new QSerialPort(DebugPortName);
    if(DebugSerialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "open" + DebugPortName + "success";
        //DebugSerialPort->setBaudRate(QSerialPort::Baud115200);
        DebugSerialPort->setBaudRate(QSerialPort::Baud38400);
        DebugSerialPort->setDataBits(QSerialPort::Data8);
        DebugSerialPort->setParity(QSerialPort::NoParity);
        DebugSerialPort->setStopBits(QSerialPort::OneStop);
        DebugSerialPort->setFlowControl(QSerialPort::NoFlowControl);

        //USB端口有数据时,处理端口数据
        connect(DebugSerialPort, SIGNAL(readyRead()), this, SLOT(DebugSerialPortRxDataHandle()));

        return true;
    }
    else
    {
       qDebug() << "open" + DebugPortName + "fail";
        return false;
    }
}

/*
 *接收调试串口数据
 */
void WorkProcessThread::DebugSerialPortRxDataHandle()
{

 /*    QByteArray DebugRxData =DebugSerialPort->readAll();// ;DebugSerialPort->readAll();
     //qDebug() << DebugRxData;
     //WriteDataToDebugSerialPort(DebugRxData);
     OBDUartData.append(DebugRxData);
     if(DebugRxData.endsWith("\r\n") == true)
     {
        //qDebug() << "start";

        //qDebug() << OBDUartData;
        UpdateOBDData(OBDUartData);
        OBDUartData.clear();
     }
*/
  OBDUartData.append(DebugSerialPort->readAll());
  if(OBDUartData.endsWith("\r\n") == true)
  {
      UpdateOBDData(OBDUartData);
      OBDUartData.clear();
  }
}


/*
 *写数据到调试端口
 */
void WorkProcessThread::WriteDataToDebugSerialPort(QByteArray WriteData)
{
    DebugSerialPort->write(WriteData);
}

void WorkProcessThread::UpdateOBDData(QByteArray obddata)
{
        //逗号分隔数目总数为15
        qint8 buf[15] = {0};
    QString str(obddata);
    for(qint8 i = 0, j = 0; i < str.length(); i++)
    {
        if(str.at(i) == ',')
        {
            buf[j] = i;
            j++;
        }
    }

    bool ok;
    qDebug() << "voltage = " << str.mid(buf[0]+1, buf[1]-buf[0]-1).toFloat(&ok);
    qDebug() << "engine speed = " << str.mid(buf[1]+1, buf[2]-buf[1]-1).toLong(&ok, 10);
    qDebug() << "runnig speed = " << str.mid(buf[2]+1, buf[3]-buf[2]-1).toLong(&ok, 10);
    qDebug() << "cur mileage = " << str.mid(buf[8]+1, buf[9]-buf[8]-1).toFloat(&ok);
    qDebug() << "sum mileage = " << str.mid(buf[9]+1, buf[10]-buf[9]-1).toLong(&ok, 10);
        qDebug() << "------------------------------";
}

/*
 * 定时器
 */
void WorkProcessThread::Time1msHandle()
{
    flag_1msTime = true;

    time1msCnt++;

    /* 5ms */
    if((time1msCnt%5) == 0)
    {
        flag_5msTime = 1;

       /* 10ms */
       if((time1msCnt%10) == 0)
       {
           flag_10msTime = 1;

           /* 50ms */
           if((time1msCnt%50) == 0)
           {
               qDebug() << "time1msCnt" << time1msCnt;
               time1msCnt = 0;
               flag_50msTime = 1;
           }
       }
    }
}

/*
 * 线程主程序
 */
void WorkProcessThread::run()
{
    //test();
//    while(1)
//    {
//        if(flag_50msTime)
//        {
//            flag_50msTime = false;
//            qDebug() << "hell";
//            Task_MG56914IHandler();
//        }
//    }
}


