#include <stdio.h> //LAB 04
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int e_prim( int x ) {
    if( x == 1 )
        return 0;
    if( x == 2 )
        return 1;
    for( int i = 2 ; i * i <= x ; i++ )
        if( x % i == 0 )
            return 0;
    return 1;
}

int cel_mai_mic_nr_prim( int n ) {
    for( int i = n - 1 ; i >= 3 ; i-- )
        if( e_prim( i ) )
            return i;
    return 0;
}

int nrCif( int x ) {
    int sol = 0;
    while( x ) {
        sol++;
        x /= 10;
    }
    return sol;
}

int trei_cifre_impare_alaturate( int x ) {
    if( x < 100 )
        return 0;
    int n = nrCif(x), cnt = 0;
    int *cifre = malloc( n * sizeof(int) );
    for( int i = 0 ; i < n ; i++ ) {
        *(cifre + i) = x % 10;
        x /= 10;
    }
    for( int i = 0, counter = 0 ; i < n ; i++ ) {
        if( *(cifre + i) % 2 ){
            counter++;
            if( counter > cnt )
                cnt = counter;
        }
        else
            counter = 0;
    }
    if( cnt >= 3 )
        return 1;
    else
        return 0;
}

int concatenare( int a, int b) {
    for( int i = 1 ; i <= nrCif(b) ; i++ ){
        a *= 10;
    }
    if( b == 0 )
        a *= 10;
    return a + b;
}

int nrEchilibrat( int n ) {
    int cifre = nrCif( n ), s1 = 0, s2 = 0;
    int *cifPoz = malloc( cifre * sizeof(int) );
    
    for( int i = 0 ; i < cifre ; i++ ) {
        *(cifPoz + i) = n % 10;
        n /= 10;
    }
    for( int i = 0 ; i < cifre ; i++ ) {
        if( i % 2 )
            s2 += *(cifPoz + i);
        else
            s1 += *(cifPoz + i);
    }
    if( s2 % 2 && !( s1 % 2) )
        return 1;
    else
        return 0;
}

int intoarcereParaImp( int x ) {
    int n, sol = 0, sol2 = 0;
    char s[100], s1[100], s2[100];
    sprintf(s, "%d", x);
    n = strlen(s);
    //printf("%ld\n", strlen(s));
    for( int i = 0 ; i < n ; i++ ) {
        if( (s[i] - '0') % 2 == 0 ){
            sol += s[i] - '0';
            sol *= 10;
        }
        else{
            sol2 += s[i] - '0';
            sol2 *= 10;
        }
    }
    sol /= 10;
    sol2 /= 10;
    sprintf(s1, "%d", sol);
    sprintf(s2, "%d", sol2);
    strcat( s1, s2 );
    
    return atoi(s1);
}

int replace_x_y(int n, int k1, int k2) {
    if( n == 0 )
        return 0;
    if( n % 10 == k1 )
        return k2 + 10 * replace_x_y( n / 10, k1, k2 );
    else
        return n % 10 + 10 * replace_x_y( n / 10, k1, k2 );
}

int main(void) {
    int n, m, k1, k2;
    scanf("%d%d%d", &n, &k1, &k2);
    printf("%d\n", replace_x_y(n , k1, k2) );
}