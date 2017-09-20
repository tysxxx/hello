
#include "include.h"
	#include "i2c.h"

/*
 * open the device
 */
int open_dev(char *file, int flag)
{
    int ret = -1;

    return ret = ::open(file, flag);
}

/*
 * close the device
 */
int close_dev(int fd)
{
    int ret = -1;
    return ret = ::close(fd);
}

/*
 * ioctl the device
 */
int ioctl_dev(int fd, char addr)
{
    int ret = -1;
    #if defined(Q_OS_LINUX)
    ret = ::ioctl(fd, I2C_SLAVE, addr);
    #endif
    return ret;
}

/*
 * sleep x us
 */
void delay_us(int us)
{
    //::delay_us(us);
    ::usleep(us);
}

void delay_ms(int ms)
{
   while(ms)
   {
     delay_us(1000);
     ms--;
   }
}




















