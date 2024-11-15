#include <ctype.h>
#include "raw/raw.h"

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