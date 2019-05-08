//
// Created by markd on 02.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

int Pow2(int n){ // нахождение 2^n
    return 1<<n;
}

void printP(int *c,int sz){
    int n = sz;
    int i,j,mn;
    mn = Pow2(n); // 2^n
    for(i=0; i < mn; i++){
        printf("{");
        for(j=0; j < n; j++)
            if ((i >> j) & 1){
                if(Pow2(j+1) >= i || ( (i != 0) && !(i &(i-1)) ) )
                    printf("%c",c[j]);
                else
                    printf("%c,",c[j]);
            }
        printf("} ");
    }
}
// P.S разобрался с (x & (x-1)):
// x = (2^n)_10 = (1000...(n нулей))_2
// x = ((2^n)-1)_10 = (11111(n единичек))_2
// -> x & (x-1) будет равен 0, если x - это 2 в n-ой степени


//всего N <= 10 -> |P(A)| = 2^10 - кол-во элементов в множестве всех подмножеств
// -> все это можно записать как последовательность бит
// abcdefghig
// 1000000000 = {a}, 0100000000 = {b} и т.д
// сдвигом большего к меньшему и конъюнкцией меньшго бита можно отсеять повторяющиеся цепочки

void P(){
    int c,i=0;
    int a[10];
    while(true){ // считываем массив
        c = getchar();
        if(c == '\n')
            break;
        else{
            a[i] = c;
            i++;
        }
    }
    printP(a,i);
}

int main() {
    P();
    return 0;
}
