/***********************************************************************************
 *
 * i2c.h
 *
 *
 * *********************************************************************************/

#ifndef I2C_H
#define I2C_H

#if defined(Q_OS_LINUX)
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#endif

ssize_t II2C_Write(int fd, char *buf, int count);
ssize_t II2C_Read(int fd, char *buf, int count);

#endif
