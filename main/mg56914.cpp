/*********************************************************************
 *
 * 光感
 *
 *
 **********************************************************************/

#include "mg56914.h"
#include "include.h"
#include "common.h"
#include "i2c.h"
#include <QDebug>
#include <QTime>
#include <QString>


//时间输出格式
#define TIME_FORMAT "hh:mm:ss.zzz"

//文件描述符
int mg56914_fd = -1;
QTime curTime;


/*
 * i2c写数据
 * fd:文件描述符
 * buf:数据
 * len:数据长度
 */
int IIC_MG56914_Write(int fd, char* buf, int len)
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
int IIC_MG56914_Read(int fd, char* buf, int len)
{
    int ret = -1;
    if(len < 2)
        return ret;
    write(fd, &buf[0], 1);   //写寄存器地址
    return ret = II2C_Read(fd, buf+1, len-1);
}

/*
 * mg5914初始化
 */
void Init_MG56914(void)
{
    char buf[2] ={0};
    qDebug() << "Init_MG56914 start";
    mg56914_fd = open_dev(MG56914_DEVICE, O_RDWR);
    if(mg56914_fd < 0)
    {
        qDebug() << "open device mg56914 fail";
    }
    else
    {
        qDebug() << "open device mg56914 ok";

        if (ioctl_dev(mg56914_fd, MG56914_ADDRESS>>1) < 0) //i2c 7bit address
        {
             qDebug() << "fail to set i2c slave address";
             close_dev(mg56914_fd);
        }
        else
        {
            qDebug() << "success to set i2c slave address";
        }
        //reg0x20  获取芯片ID
        buf[0] = 0x20;
        buf[1] = 0x00;
        IIC_MG56914_Read(mg56914_fd, buf, 2);
        qDebug() << "mg56914 id is " << (uint8_t)buf[1];
        if(buf[1] != MG56914_ID)
            return;

        qDebug() << "mg56914 ok ";
       //reg0x00
        buf[0] = 0x00;
        buf[1] = MG56914_REG0x00;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
        //reg0x01
        buf[0] = 0x01;
        buf[1] = MG56914_ALS_INTT_32 | MG56914_ALS_GAIN_LOW;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
        //reg0x02
        buf[0] = 0x02;
        buf[1] = MG56914_ALS_FILTER16;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
        //reg0x07
        buf[0] = 0x07;
        buf[1] = 0x10;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
        //reg0x12
        buf[0] = 0x12;
        buf[1] = 0x02;
        IIC_MG56914_Write(mg56914_fd, buf, 2);

        buf[0] = 0x07;
        buf[1] = 0x00;
        IIC_MG56914_Read(mg56914_fd, buf, 2);
        qDebug() << "mg56914 reg0x07 is " << (uint8_t)buf[1];

        //reg0x11
        buf[0] = 0x11;
        buf[1] = MG56914CHIP_ACTIVE | MG56914CHIP_RESETN_RESET;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
        delay_ms(200);
        //reg0x11
        buf[0] = 0x11;
        buf[1] = MG56914CHIP_ACTIVE | MG56914CHIP_RESETN_RUN;
        IIC_MG56914_Write(mg56914_fd, buf, 2);
    }
}


void AlsToAdjustPWM(als_level alsLevel)
{
    printf("----------------alsLevel = %d---------------------\r\n",alsLevel);
    switch(alsLevel)
    {
        case ALS_LEVEL0:
            //MX_ChangePWMDuty(600);
            break;
        case ALS_LEVEL1:
            //MX_ChangePWMDuty(1500);
            break;
        case ALS_LEVEL2:
            //MX_ChangePWMDuty(5000);
            break;
        case ALS_LEVEL3:
            //MX_ChangePWMDuty(10000);
            break;
        case ALS_LEVEL4:
            //MX_ChangePWMDuty(32000);
            break;
        case ALS_LEVEL5:
            //MX_ChangePWMDuty(59999);
            break;
        default:
            break;
    }
}



#define	MAX_SAMPLE_CNT   10 //20
#define	VAL_UNCHANGE	 3  //5


uint16_t sampleValue[MAX_SAMPLE_CNT] = {0};
uint16_t curAlsData = 0;
als_level detAlsLevel;
als_level curAlsLevel;
uint16_t alsData = 0;
bool f_alsAdjustDown = 0;
bool f_alsAdjustUp = 0;
uint8_t alsLevelDetCnt;
uint8_t firstSample = 0, sampleCnt = 0;

/*
 * 光感数据处理
 */
void Task_MG56914IHandler(void)
{
    char buf[2] = {0};
    uint16_t maxAlsData = 0, minAlsData = 0;
    uint8_t i = 0, eqCnt = 0, gtCnt = 0, ltCnt = 0;
    uint16_t gtValue[MAX_SAMPLE_CNT] = {0};
    uint16_t ltValue[MAX_SAMPLE_CNT] = {0};

    qDebug() << "current time = " << curTime.currentTime().toString("hh:mm:ss.zzz");

//    //@.轮询读取光感值
//    buf[0] = 0x15;
//    buf[1] = 0x00;
//    IIC_MG56914_Read(mg56914_fd, buf, 2);
//    alsData = buf[1];
//    buf[0] = 0x16;
//    buf[1] = 0x00;
//    IIC_MG56914_Read(mg56914_fd, buf, 2);
//    alsData |= buf[1] << 8 +'0'-'0';

    qDebug() << "alsData = " << alsData;

    //@.处理光感
    if(firstSample == 0)
    {
        //1.获取第一次采样基准值
        curAlsData = alsData;
        firstSample = 1;
        sampleCnt = 0;
        printf("firstSample alsdat=%d\r\n", alsData);
    }
    else
    {
        if(sampleCnt < MAX_SAMPLE_CNT)
        {
            //保存全部采样次数的值
            sampleValue[sampleCnt++] = alsData;
        }
        else
        {
            sampleCnt = 0;
            eqCnt = 0;
            gtCnt = 0;
            ltCnt = 0;

            //2.采样接收后
            for(i = 0; i < MAX_SAMPLE_CNT; i++)
            {
                //printf("sampleValue[%d]=%d\r\n", i, sampleValue[i]);
                if(sampleValue[i] > curAlsData)
                {
                    gtValue[gtCnt++] = sampleValue[i];
                }
                else if(sampleValue[i] < curAlsData)
                {
                    ltValue[ltCnt++] = sampleValue[i];
                }
                else  //相等表示没有变化
                {
                    eqCnt++;
                }
            }

//			printf("gtCnt = %d\r\n", gtCnt);
//			printf("ltCnt = %d\r\n", ltCnt);
//			printf("eqCnt = %d\r\n", eqCnt);

            //3.根据分布的情况重新计算基准值
            if(eqCnt <= VAL_UNCHANGE) //数据跳变的次数
            {
                if(gtCnt > ltCnt)
                {
                    minAlsData = gtValue[0];
                    for(i = 0; i < gtCnt; i++)	//大值域里面的小值
                    {
                        if(minAlsData > gtValue[i])
                            minAlsData = gtValue[i];
                        //printf("gtValue[%d] = %d\r\n", i, gtValue[i]);
                    }
                    curAlsData = minAlsData;
                }
                else if(gtCnt <= ltCnt)		//小值域里面的大值
                {
                    maxAlsData = ltValue[0];
                    for(i = 0; i < ltCnt; i++)
                    {
                        if(maxAlsData < ltValue[i])
                            maxAlsData = ltValue[i];
                        //printf("ltValue[%d] = %d\r\n", i, ltValue[i]);
                    }
                    curAlsData = maxAlsData;
                }
            }

            printf("curAlsData = %d\r\n", curAlsData);

            //4.判断光感值的范围
            if(curAlsData <= 100){detAlsLevel = ALS_LEVEL0;}
            else if(curAlsData <= 200){detAlsLevel = ALS_LEVEL1;}
            else if((curAlsData >= 500) && (curAlsData <= 2000)){detAlsLevel = ALS_LEVEL2;}
            else if(curAlsData <= 10000){detAlsLevel = ALS_LEVEL3;}
            else if(curAlsData <= 30000){detAlsLevel = ALS_LEVEL4;}
            else if(curAlsData > 30000){detAlsLevel = ALS_LEVEL5;}

            //5.根据光感值调节PWM值,渐变过程.
            if(detAlsLevel > curAlsLevel)
            {
                f_alsAdjustDown = 0;

                if(f_alsAdjustUp)
                {
                    if(alsLevelDetCnt++ >= 3) //0.8s (n+1)
                    {
                        alsLevelDetCnt = 0;
                        //curAlsLevel += 1;
                        AlsToAdjustPWM(curAlsLevel);
                    }
                }
                else
                {
                    f_alsAdjustUp = 1;
                    alsLevelDetCnt = 0;
                }
            }
            else if(detAlsLevel < curAlsLevel)
            {
                f_alsAdjustUp = 0;

                if(f_alsAdjustDown)
                {
                    if(alsLevelDetCnt++ >= 3)
                    {
                        alsLevelDetCnt = 0;
                        //curAlsLevel = curAlsLevel-1;
                        AlsToAdjustPWM(curAlsLevel);
                    }
                }
                else
                {
                    f_alsAdjustDown = 1;
                    alsLevelDetCnt = 0;
                }
            }
            else
            {
                f_alsAdjustUp = 0;
                f_alsAdjustDown = 0;
                alsLevelDetCnt = 0;
            }

        }
    }

}
