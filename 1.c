//
// Created by markd on 02.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

bool isPrime(unsigned int n){
    assert((n != 0) && (n != 1)); // проверка на n = 0 или n = 1
    // можем пройти до sqrt(n), т.к любое не простое m представляется в виде
    // m = a * b, где a - простое
    // исходя из этого можно заметить, что min(a,b) <= sqrt(n)
    // поэтому при последовательном переборе до sqrt(n) мы точно его найдем
    for(int i = 2; i*i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

void testPrime(unsigned int n){
    if(isPrime(n))
        printf("%i - is prime number\n",n);
    else
        printf("%i - isn't prime number\n",n);
}

int main(void){
    int i = 2 , n = 0;
    while(true){
        if(n == 50)
            break;
        if (isPrime(i)){
            printf("%d ",i);
            n++;
        }
        i++;
    }
//    getchar();
//    testPrime(359);
//    testPrime(172);

//    testPrime(0); //Assertion failed!
//    testPrime(1); //Assertion failed!
    return 0;

}
