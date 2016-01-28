#ifndef OTHERS_H
#define OTHERS_H

#include <stdio.h>
#include <stdarg.h>

void printdebug( const char * format, ... )
__attribute__ ((format (printf, 1, 2)));

#endif