#include "others.h"

void printdebug( const char * format, ... ){   
#if DEBUG
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}