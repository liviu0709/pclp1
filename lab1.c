#include <stdio.h> //LAB 03
#include <stdlib.h>
#include <time.h>
#include <math.h>

void prob1() {
    int n = 100;
    for( int i = 1 ; i <= n ; i++) {
        if( i % 3 == 0 && i % 5 == 0 )
            printf("FizzBuzz ");
        else if( i % 3 == 0 )
            printf("Fizz ");
            else if( i % 5 == 0 )
                printf("Buzz ");
                else
                    printf("%d ", i);

    }
}

int ePrim( int x ) {
    if( x == 1 )
        return 0;
    if( x == 2 )
        return 0;
    for( int i = 2 ; i * i <= x ; i++ )
        if( x % i == 0 )
            return 0;
    return 1;
    
}

void prob2() {
    int x = 0, max1 = 0, max2 = 0;
    while( x >= 0 ) {
        scanf("%d", &x);
        if( ePrim( x ) && x > 0 ) {
            if( x > max1 && x > max2 ){
                max2 = max1;
                max1 = x;
            }
            else if( x > max2 && x != max1 )
                max2 = x;
        }
    }
    printf("Maxmele sunt: %d %d\n", max1, max2);
}

int sumCif( int x ) {
    int sol = 0;
    while( x ) {
        sol += x % 10;
        x /=10;
    }
    return sol;
}

void prob3() {
    int n;
    scanf("%d", &n);
    while( n % 100 > 9 ) {
        n = sumCif( n );
        printf("%d\n", n);
    }
}

void prob4_fara_vectori() {
    int n, x, sum = 0;
    scanf("%d", &n);
    for( int i = 0 ; i < n + 1 ; i++ ) {
        scanf("%d", &x);
        sum += x;
    }
    printf("%d\n", sum - n * (n + 1) / 2 );
}

void prob4() {
    int n, x;
    scanf("%d", &n);
    int *interval = malloc( (n + 1) * sizeof(int) );
    for( int i = 0 ; i < n + 1 ; i++ ) {
        scanf("%d", &x);
        *(interval + x - 1) += 1; 
    }
    for( int i = 0 ; i < n ; i++ ) {
        if( *(interval + i) == 2 )
            printf("%d\n", i + 1); 
    }
}

// 5|Se citesc numere de la tastatura pana la intalnirea unui numar negativ. 
//Sa se afle care este numarul citit ce are cei mai multi divizori, precum si cate patrate perfecte au fost citite.

int nrDiv(int x) {
    int cnt = 0;
    for( int i = 1 ; i <= x ; i++ ) {
        if( x % i == 0 )
            cnt++;
    }
    return cnt;
}

void prob5() {
    int x = 0, nrMaxDiv = 0, pp = 0, nrMax;
    while( x >= 0 ) {
        scanf("%d", &x);
        if( nrDiv(x) > nrMaxDiv ) {
            nrMaxDiv = nrDiv(x);
            nrMax = x;
        }
        if( (int) sqrt(x) * sqrt(x) == x )
            pp++;
    }
    printf("Numarul cu nr max de div este: %d\n", nrMax);
    printf("Au fost citite %d patrate perfecte\n", pp);
}

int main(void){
    prob5();
}