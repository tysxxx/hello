

#include "include.h"
#include "common.h"
#include "i2c.h"
#include "mg5691x_gesture.h"
#include "mg56913.h"
#include <QDebug>

#define GES_ENABLE  1

#if GES_ENABLE
//#include "mg5691x_gesture.h"
#endif


#if GES_ENABLE
unsigned short epl_buf[48];
unsigned short ges_buffer[8][4] = {{0}};
unsigned short ges_data[4] = {0};

#endif

GESTURE_DIRECTION GestureDirection;
uint8_t Event_Occur;
uint8_t MG56913TxBuf[10];
uint16_t mg56913Cnt;


 //文件描述符
int mg56913_fd = -1;

/*
 * i2c写数据
 * fd:文件描述符
 * buf:数据
 * len:数据长度
 */
int IIC_MG56913_Write(int fd, char* buf, int len)
{
    int ret = -1;
    return ret = II2C_Write(fd, buf, len);
}

/*
 * i2c读取数据
 * fd:文件描述符
 * buf:数据
 * len:数据长度
 */
int IIC_MG56913_Read(int fd, char* buf, int len)
{
    int ret = -1;
    if(len < 2)
        return ret;
    write(fd, &buf[0], 1);   //写寄存器地址
    return ret = II2C_Read(fd, buf+1, len-1);
}

/*
 * mg5913初始化
 */
void Init_MG56913(void)
{
    char buf[2] ={0};
    qDebug() << "Init_MG56913 start";
    mg56913_fd = open_dev(MG56913_DEVICE, O_RDWR);
    if(mg56913_fd < 0)
    {
        qDebug() << "open device mg56913 fail";
    }
    else
    {
        qDebug() << "open device mg56913 ok";

        if (ioctl_dev(mg56913_fd, MG56913_ADDRESS>>1) < 0) //i2c 7bit address
        {
             qDebug() << "fail to set i2c slave address";
             close_dev(mg56913_fd);
        }
        else
        {
            qDebug() << "success to set i2c slave address";
        }
        //reg0x20  获取芯片ID
        buf[0] = 0x20;
        buf[1] = 0x00;
        IIC_MG56913_Read(mg56913_fd, buf, 2);
        qDebug() << "mg56913 id is " << (uint8_t)buf[1];
        if(buf[1] != MG56913_ID)
            return;

             qDebug() << "mg56913 ok ";
       //reg0x00
        buf[0] = 0x00;
        buf[1] = MG56913I_REG0x00;
        IIC_MG56913_Write(mg56913_fd, buf, 2);
        //reg0x24
        buf[0] = 0x24;
        buf[1] = MG56913I_REG0x24;
        IIC_MG56913_Write(mg56913_fd, buf, 2);
        //reg0x25
        buf[0] = 0x25;
        buf[1] = MG56913I_REG0x25;
        IIC_MG56913_Write(mg56913_fd, buf, 2);

        //reg0x11
        buf[0] = 0x11;
        buf[1] = CHIP_POWER_ON | CHIP_RESETN_RESET;
        IIC_MG56913_Write(mg56913_fd, buf, 2);
        delay_ms(200);
        //reg0x11
        buf[0] = 0x11;
        buf[1] = CHIP_POWER_ON | CHIP_RESETN_RUN;
        IIC_MG56913_Write(mg56913_fd, buf, 2);
    }
}


void Task_MG56913IHandler(void)
{

}



