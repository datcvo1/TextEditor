#ifndef KEYS_H
#define KEYS_H

#include <sys/ioctl.h>
#include <string.h>
#include "../error/error.h"
#include "../raw/raw.h"

typedef struct buffer
{
    char* buf;
    int len;
} buffer;

void processKeyPress();
void refreshScreen();

#endif