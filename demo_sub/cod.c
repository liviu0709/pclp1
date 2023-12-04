#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX	100
 
void magic(int a[MAX], int n)
{
	int i;
 
	for (i = 0; i < n; i++)
		a[i] = a[i] & (~(0x01 & 0x42));
    //n % 2 ? n/ 2+ 1 : n/2
	for (i = 0; i <  n/2 ; i++) {
		a[i] = a[i] ^ a[n - 1 - i];
		a[n - 1 - i] = a[i] ^ a[n - 1 - i];
		a[i] = a[i] ^ a[n - 1 - i];
	}
    strcat(a + n, "hello");
	for (i = 0; i < n; i++);
	
 
}
 
char *incptr(char *p) {
  return ++p;
}

int main(void)
{
	int a[MAX], n, i;
    scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
 
	magic(a , n );
 
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
    printf("\n");
    // printf("%s", incptr(NULL)); e gresit doar daca e fol valoarea returnata
    int *x = malloc(sizeof(int) * 100000000);
    for( int i = 0 ; i < 100000000; i++)
        x[i] = i;
    while(1);
	return 0;
}
