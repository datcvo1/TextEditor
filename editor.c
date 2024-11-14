#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

struct termios origMode;

void fatalError(const char* errMsg)
{
    perror(errMsg);     //print errMsg, then info related to current "errno"
    exit(1);
}

void disableRaw()
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &origMode) == -1)
        fatalError("tcssetattr failed on shutdown");
}

void enableRaw()
{
    // get attributes from a terminal associated with given file descriptor, STDIN_FILENO, and place them in termios struct
    struct termios rawMode;
    if(tcgetattr(STDIN_FILENO, &origMode) == -1)
        fatalError("tcsgetattr failed");
    rawMode = origMode;

    // "ICANON" is a bitflag, "~"" is bitwise NOT. "~ ICANON" turns off canonical mode, now process input byte by byte
    // bitwise "&" on flags field to change only specified flags and leave the rest the same
    // "~ ECHO" turns off printing key inputs to the terminal
    // "~ ISIG, IXON, IEXTEN, ICRNL" turns off various signals like ctrl+c, ctrl+s
    // "~ OPOST" adds carriage returns to newlines i.e. "\r\n" instead of "\n".
    rawMode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    rawMode.c_oflag &= ~(OPOST);
    rawMode.c_cflag |= (CS8);
    rawMode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // readjust read() behavior. Instead of waiting forever, read() waits for (VTIME value)/10 of a second before returning 0
    rawMode.c_cc[VMIN] = 0;
    rawMode.c_cc[VTIME] = 1;


    // apply changes to object(terminal in this case) associated with fd STDIN_FILENO, using termios termInfo, with condition that     
    // changes apply after all queued output is written to object and flush all unread inputs   
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawMode) == -1)
        fatalError("tcssetattr failed on startup");

    // return terminal to original state on program exit
    atexit(disableRaw);
}

int main()
{
    // when program is executed, stdin STDIN_FILENO receives input from terminal, set to canonical/cooked mode; i.e. input is only sent on "Enter"
    // text editor needs to process every keypress regardless of newline, i.e. raw mode
    enableRaw();

    // read() from a file descriptor, STDIN_FILENO == file descriptor no.0, for stdin. Remember that file descriptors are unique numbered
    // read() returns amount bytes read. 0 for eof. 
    while(1)
    {
        char c = '\0';
        // iscntrl returns non 0 if non-printable control character, else return 0
        // NOTE: need carriage return "/r" to bring cursor back to the left edge on each newline due to "~ OPOST"
        if(read(STDIN_FILENO, &c, 1) == -1)
            fatalError("read failure");

        if(c == 'q') break;
        if(iscntrl(c))
            printf("%d\r\n", c);
        else
            printf("%d '%c'\r\n", c, c);
    }

    return 0;
}