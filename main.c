#include <ctype.h>
#include "raw/raw.h"
#include "keys/keys.h"

int main()
{
    // when program is executed, stdin STDIN_FILENO receives input from terminal, set to canonical/cooked mode; i.e. input is only sent on "Enter"
    // text editor needs to process every keypress regardless of newline, i.e. raw mode
    enableRaw();

    while(1)
    {
        refreshScreen();
        processKeyPress();
    }

    return 0;
}