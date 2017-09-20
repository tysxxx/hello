#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "work.h"
#include <QDebug>
#include <QFile>


//主线程内工作:显示图片
//子线程内工作:整个程序运行,uart,usb串口通信,i2c通信.
//主线程和子线程通过信号与槽进行相关联.

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);


//    qint8 buf[5] = {4, 5 , 6, 7 ,8};
//    qDebug() << *buf;
//    qDebug() << *(buf+1);
//    qDebug() << *(buf+2);
//    qDebug() << *(buf+3);
//    qDebug() << *(buf+4);

    //窗口不可关闭
//    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint
//                         &~Qt::WindowMinMaxButtonsHint);

    //setGeometry(SCREEN_X_POS, SCREEN_Y_POS, SCREEN_LENGTH, SCREEN_WIDTH);
    HasReadHead = false;
    USBSerialData.clear();
    AvalibleNum = 165167;

    workThread = new WorkProcessThread();
    workThread->start();

    //打开USB串口
    //OpenUSBSerialPort(USBSERIALPORTNAME);
/*
    QVideoWidget *videoWidget = new QVideoWidget;
    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    setLayout(layout);

    mediaPlayer.setVideoOutput(videoWidget);
    videoWidget->setGeometry(150, 150, 480, 240);
*/
   // label = new QLabel();
   // label->setPixmap(QPixmap("F:\company\load1.jpg"));
//    QString filename;
//    filename=QFileDialog::getOpenFileName(this,
//                                              tr("选择图像"),
//                                              "",
//                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
//    QImage myImage;
//    myImage.load("C:/Users/Administrator/Desktop/load3.jpg");
//    //qDebug() << "filepath= " << filename;
//    ui->labelimage->setGeometry(0, 0, 480, 240);
//   // ui->labelimage->setPixmap(QPixmap::fromImage(myImage).scaled(ui->labelimage->size()));
//   // ui->labelimage->setPixmap(QPixmap("F:\company\load1.jpg"));
//    ui->labelimage->setPixmap(QPixmap::fromImage(myImage));

    //mediaPlayer.setMedia(QUrl("F:/friendlyArm/B/Test Video/Michael_Jackson_-_Hollywood_Tonight_1080p.mp4"));
#if 0
    QFile file("./video.mp4");
    if(!file.open(QIODevice::ReadOnly))
    qDebug() << "Could not open file";

    mediaPlayer.setMedia(QUrl::fromLocalFile("E:/me/2017/2017-09/px3se/app/version0.3/px3seApp/video.mp4"));
#elif 0
    mediaPlayer.setMedia(QUrl("./video.mp4"));
#endif
    //mediaPlayer.play();
}

MainWidget::~MainWidget()
{
    delete ui;
}

/*
 * 打开USB串口
 */
bool MainWidget::OpenUSBSerialPort(QString USBSerialPortName)
{
    USBSerialPort = new QSerialPort(USBSerialPortName);
    if(USBSerialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "open" + USBSerialPortName + "success";
        USBSerialPort->setBaudRate(QSerialPort::Baud115200);
        USBSerialPort->setDataBits(QSerialPort::Data8);
        USBSerialPort->setParity(QSerialPort::NoParity);
        USBSerialPort->setStopBits(QSerialPort::OneStop);
        USBSerialPort->setFlowControl(QSerialPort::NoFlowControl);

        //USB端口有数据时,处理端口数据
        connect(USBSerialPort, SIGNAL(readyRead()), this, SLOT(USBSerialPortDataHandle()));
        connect(this, SIGNAL(USBSerialRxDataFinished(QByteArray)),
                this, SLOT(ShowNewImage(QByteArray)));

        return true;
    }
    else
    {
       qDebug() << "open" + USBSerialPortName + "fail";
        return false;
    }
}

/*
 * 处理USB串口的数据
 */
void MainWidget::USBSerialPortDataHandle()
{
    QByteArray ReadUsbSerialPortData = USBSerialPort->readAll();

#ifdef OS_WINDOW
    USBSerialData.append(ReadUsbSerialPortData);
    //WriteDataToUsbSerial(ReadUsbSerialPortData);
    if(USBSerialData.length() >= AvalibleNum)
    {
        ImageData = USBSerialData;
        emit USBSerialRxDataFinished(ImageData);
    }
#else

    if(HasReadHead)
    {
         USBSerialData.append(ReadUsbSerialPortData);
         if(USBSerialData.length() >= AvalibleNum)
         {
             ImageData = USBSerialData;
             emit USBSerialRxDataFinished(ImageData);
             HasReadHead = false;
         }
    }
    else
    {
        bool ok = 0;
        HasReadHead = true;

        USBSerialData.clear();
        QByteArray tmp(ReadUsbSerialPortData);
        qint8 tmpSize = tmp.size();

        //数据前4个字节用于存放图片的大小
        AvalibleNum = tmp.left(4).toHex().toLongLong(&ok, 16);
        ReadUsbSerialPortData.remove(0,4);
        USBSerialData.append(ReadUsbSerialPortData);

        qDebug() << "receive the usb serial data length is "<< AvalibleNum;
        if(tmpSize <= 4)
        {
            qDebug()<< USBSerialData;
        }

        if(USBSerialData.length() >= AvalibleNum) //判断数据是否接收完毕
        {
            ImageData = USBSerialData;
            emit USBSerialRxDataFinished(ImageData);
            HasReadHead = false;
        }
    }
#endif
}

/*
 显示图片
 */
void MainWidget::ShowNewImage(QByteArray ImageData)
{
    QPalette palette;
    QImage image=QImage::fromData(ImageData,IMAGE_FORMAT);
    palette.setBrush(QPalette::Background, QBrush(image)); //背景
    this->setPalette(palette);
}

/*
 * 写数据到USB串口
 */
void MainWidget::WriteDataToUsbSerial(QByteArray WriteData)
{
    USBSerialPort->write(WriteData);
}





































































