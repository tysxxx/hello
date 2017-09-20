#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QImage>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QByteArray>
#include <QLabel>
#include <QFileDialog>



#include "work.h"

//端口定义
#if defined(Q_OS_WIN32)
#define OS_WINDOW
#define USBSERIALPORTNAME "COM3"
#define IMAGE_FORMAT "JPG"
#else
#define USBSERIALPORTNAME "/dev/ttyGS0"
#define IMAGE_FORMAT "PNG"
#define OBD_UART    "/dev/ttySCA0"
#endif

//显示屏幕的起始位置和长,宽
#define SCREEN_X_POS    10
#define SCREEN_Y_POS    10
#define SCREEN_LENGTH   480
#define SCREEN_WIDTH    240

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    bool OpenUSBSerialPort(QString USBSerialPortName);
    void WriteDataToUsbSerial(QByteArray WriteData);

signals:
    void USBSerialRxDataFinished(QByteArray ImageData);

public slots:
    void ShowNewImage(QByteArray ImageData);
    void USBSerialPortDataHandle();

private:
    Ui::MainWidget *ui;
    WorkProcessThread *workThread;

    QSerialPort *USBSerialPort;

    QByteArray USBSerialData;
    QByteArray ImageData;

    bool HasReadHead;
    quint32 AvalibleNum;

   QMediaPlayer mediaPlayer;
   QLabel *label;
};

#endif // MAINWIDGET_H
