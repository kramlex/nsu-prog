//
// Created by markd on 02.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

void putV(int *a, int *k){
	if(!a)
		exit(EXIT_FAILURE); // проверка на передачу указателя в функцию
    int c = 0;
    bool neg = false;
    bool notSpace = false;
    int l=0;
    while(1){
        c = getchar();
        if(c == ' ' && notSpace) {
            notSpace = false;
            if(neg) l *= -1;
            neg = 0;
            a[(*k)] = a[(*k)] * l;
            (*k)++;
            l = 0;
        }
        if(c == '-')
            neg = true;
        if(c == '\n') {
            if(neg)
                l *= -1;
            a[(*k)] *= l;
            break;
        }
        else if(c != ' ' && c != '\n' && c != '-'){
            notSpace = true;
            l = l*10 + (c-'0');
        }
    }
}

void scalarProduct(){
    int *a = (int*)malloc(1001*sizeof(int)); // выделение памяти под массив ( заполнение нулями )
    if(a == NULL){
        exit(EXIT_FAILURE); // проверка на выделение памяти функцией malloc
    }
    int k = 0;
    for(int i = 0; i < 1001; i++)
        a[i] = 1;
    putV(a,&k);
    k = 0;
    putV(a,&k);
    int res = 0;
    for(int i = 0; i <=k ; i++ )
        res += a[i];
    free(a); // P.S добавил free()
    printf("%d",res); // вывод результата
}

int main() {
    scalarProduct();
    return 0;
}