#include "error.h"

void fatalError(const char* errMsg)
{
    perror(errMsg);     //print errMsg, then info related to current "errno"
    exit(1);
}