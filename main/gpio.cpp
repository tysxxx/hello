/***********************************************************************************
 *
 *  gpio.cpp
 *
 *
 * *********************************************************************************/

#include "gpio.h"
#include "include.h"
#include "common.h"
#include <QDebug>


#define SYSFS_GPIO_EXPORT           "/sys/class/gpio/export"
#define SYSFS_GPIO_RST_DIR          "/sys/class/gpio/gpio48/direction"
#define SYSFS_GPIO_RST_DIR_VAL      "OUT"
#define SYSFS_GPIO_RST_VAL          "/sys/class/gpio/gpio48/value"
#define SYSFS_GPIO_RST_VAL_H        "1"
#define SYSFS_GPIO_RST_VAL_L        "0"

void GPIO_Init(uint8_t gpioNumb, uint8_t direction, uint8_t status)
{
    FILE *p=NULL;
    int i=0;
    p = fopen("/sys/class/gpio/export","w");
    fprintf(p,"%d",122);
    fclose(p);
    p = fopen("/sys/class/gpio/gpio122/direction","w");
    fprintf(p,"out");
    fclose(p);
    for(i=0;i<100;i++)
    {
    p = fopen("/sys/class/gpio/gpio122/value","w");
    fprintf(p,"%d",1);

    delay_ms(1000);
    fclose(p);
    p = fopen("/sys/class/gpio/gpio122/value","w");
    fprintf(p,"%d",0);
    sleep(1);
    fclose(p);
    }
    p = fopen("/sys/class/gpio/unexport","w");
    fprintf(p,"%d",122);
    fclose(p);
    return ;
}


void test(void)
{
    //FILE *p=NULL;
    char *p = NULL;
    int i=0;

    //p = ::fopen("/sys/class/gpio/gpio122/direction","w");
    p = "/sys/class/gpio/gpio122/direction";
    ::sprintf(p,"%s");
    //::printf("---1.%s---",p);
    //qDebug() << p;

    //::fclose(p);

    //p = ::fopen("/sys/class/gpio/gpio122/value","w");
    //::fprintf(p,"%d",1);
    //::printf("---2.%s---",p);
    //qDebug() << p;
    //::fclose(p);
}
