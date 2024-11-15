#ifndef RAW_H
#define RAW_H

#include <unistd.h>
#include <termios.h>
#include "../error/error.h"

typedef struct EditorState
{
    struct termios origMode;
    int rows;
    int cols;
} EditorState;

extern EditorState state;   //variable needs to be re-declared and/or defined in c file

void enableRaw();
void getState();

#endif