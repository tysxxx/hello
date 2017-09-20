
#include "include.h"
#include "i2c.h"

ssize_t II2C_Write(int fd, char *buf, int count)
{
    ssize_t ret = -1;
    return ret = ::write(fd, buf, count);
}

ssize_t II2C_Read(int fd, char *buf, int count)
{
    ssize_t ret = -1;
    return ret = ::read(fd, buf, count);
}
