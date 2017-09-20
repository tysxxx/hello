#ifndef COMMON_H
#define COMMON_H

#include "include.h"



/*****************************************/
//
/*****************************************/
int open_dev(char *file, int flag);
int close_dev(int fd);
int ioctl_dev(int fd, char addr);
void delay_us(int us);
void delay_ms(int ms);


#endif
