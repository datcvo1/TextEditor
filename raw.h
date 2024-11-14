#ifndef RAW_H
#define RAW_H

#include <unistd.h>
#include <termios.h>
#include "error.h"

void disableRaw();
void enableRaw();

#endif