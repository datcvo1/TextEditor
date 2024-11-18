#include "keys.h"

// Ctrl key zeroes bytes 5 and 6 from other keys(byte count starts from 0)
// this function simulates this effect by applying bitwise "&" to parameter "key" with 0x1f(00011111)
static char ctrlKey(char key)
{
    // "ctrl + a to z" maps to bytes 1-26. 
    return key & 0x1f;
}

static char readKey()
{
    char c = '\0';
    int isIdle;
    // read() from a file descriptor, STDIN_FILENO == file descriptor no.0, for stdin. Remember that file descriptors are unique numbered
    // read() returns amount bytes read. NOTE: raw mode changes behavior of read(). Returns 0 after waiting for 1/10 second with no input. 
    while(!(isIdle = read(STDIN_FILENO, &c, 1)))
        if(isIdle == -1) fatalError("read failure");

    return c;
}

static void append(buffer* appBuf, char* str, int len)
{
    char* newStr = realloc(appBuf->buf, appBuf->len + len);
    if(!newStr) return;

    memcpy(&newStr[appBuf->len], str, len);
    appBuf->buf = newStr;
    appBuf->len += len;
}

static void drawLeftBorder(buffer* leftBorder)
{
    for(int i = 0; i < state.rows; i++)
    {
        if(i == state.rows - 1)             // fixes bug where last row doesnt have "|"
            append(leftBorder, "|", 2);
        else
            append(leftBorder, "|\r\n", 4);
    }
}

void refreshScreen() 
{
    buffer leftBorder = { NULL, 0 };

    // write to terminal "\x1b" (escape character, 27 in decimal) followed by "["
    // escape sequences always start with escape character then [
    // 2J is the command. J for Erase in Display command, with parameter 2 meaning erase all lines
    append(&leftBorder, "\x1b[2J", 5);
    // H with default parameters move cursor to home, top left
    append(&leftBorder, "\x1b[H", 4);
    drawLeftBorder(&leftBorder);
    append(&leftBorder, "\x1b[H", 4);

    write(STDOUT_FILENO, leftBorder.buf, leftBorder.len);
    free(leftBorder.buf);
}

void processKeyPress()
{
    char k = readKey();

    if(ctrlKey('q') == k)
    {
        refreshScreen();
        exit(0);  //exit on ctrl+q
    }
}

