#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

int max( int num, ... ) {
    va_list valist;
    int sol;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
        int x = va_arg(valist, int);
        if( i == 0 )
            sol = x;
        if( x > sol )
            sol = x;
    }
    va_end(valist);
    return sol;
}

int min( int num, ... ) {
    va_list valist;
    int sol;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
        int x = va_arg(valist, int);
        if( i == 0 )
            sol = x;
        if( x < sol )
            sol = x;
    }
    va_end(valist);
    return sol;

}