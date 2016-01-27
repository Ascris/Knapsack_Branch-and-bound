#ifndef OTHERS_H
#define OTHERS_H

#include <stdio.h>
#define DEBUG 1

void printdebug( const char * format, ... ){   
#if DEBUG
    va_list ap;
    printf(format, ap);
#endif
}

#endif