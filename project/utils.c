#include <math.h>
#include <stdlib.h>

char* int2char(int number){
    int n = log10(number) + 1;
    int i;
    char *numberArray = calloc(n, sizeof(char));
    for (i = n-1; i >= 0; --i, number /= 10)
    {
        numberArray[i] = (number % 10) + '0';
    }
	numberArray[n] ='C';
    return numberArray;
}
