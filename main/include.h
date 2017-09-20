#ifndef INCLUDE_H
#define INCLUDE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#endif

#endif
