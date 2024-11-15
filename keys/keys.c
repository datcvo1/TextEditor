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

static void drawLeftBorder()
{
    for(int i = 0; i < 25; i++)
    {
        write(STDOUT_FILENO, "|\r\n", 3);
    }
}

void refreshScreen() 
{
    // write to terminal "\x1b" (escape character, 27 in decimal) followed by "["
    // escape sequences always start with escape character then [
    // 2J is the command. J for Erase in Display command, with parameter 2 meaning erase all lines
    write(STDOUT_FILENO, "\x1b[2J", 4);
    // H with default parameters move cursor to home, top left
    write(STDOUT_FILENO, "\x1b[H", 3);
    drawLeftBorder();
    write(STDOUT_FILENO, "\x1b[H", 3);
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

