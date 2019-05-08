//
// Created by markd on 02.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

int int_to_char(unsigned int n) {
    switch (n) {
        case 0 :
            return '0';
        case 1 :
            return '1';
        case 2 :
            return '2';
        case 3 :
            return '3';
        case 4 :
            return '4';
        case 5 :
            return '5';
        case 6 :
            return '6';
        case 7 :
            return '7';
        case 8 :
            return '8';
        case 9 :
            return '9';
        case 10 :
            return 'A';
        case 11 :
            return 'B';
        case 12 :
            return 'C';
        case 13 :
            return 'D';
        case 14 :
            return 'E';
        case 15 :
            return 'F';
    }
    return 0;
}

int char_to_int(char n) {
    switch (n) {
        case '0' :
            return 0;
        case '1' :
            return 1;
        case '2' :
            return 2;
        case '3' :
            return 3;
        case '4' :
            return 4;
        case '5' :
            return 5;
        case '6' :
            return 6;
        case '7' :
            return 7;
        case '8' :
            return 8;
        case '9' :
            return 9;
        case 'A' :
            return 10;
        case 'B' :
            return 11;
        case 'C' :
            return 12;
        case 'D' :
            return 13;
        case 'E' :
            return 14;
        case 'F' :
            return 15;
    }
    return 0;
}

void interpretation10_to(unsigned int x, unsigned int to){ // перевод числа x из 10-ой СС в СС to
    char *str = (char*)malloc(18 * sizeof(char)); // 18 = 17 + 1 , т.к 17 - длинна числа 10^5 в двоичной системе счисления
    if(!str) 
		exit(EXIT_FAILURE); // проверка на выделение памяти функцией malloc
    int k = 0; // кол-во символов в СС to десятичного числа num
    int num = x; // само число в 10ой СС
    while (num){
        str[k] = int_to_char(num % to);
        num /= to;
        k++;
    }
    for(int i= k-1; i>= 0; i--)
        printf("%c",str[i]);
    free(str); // добавил очищение выделенной памяти
}

void interpretation(){
    unsigned int in,out;
    char *s = (char*)malloc(18 * sizeof(char));
	if(!s)
		exit(EXIT_FAILURE); // проверка на выделение памяти функцией malloc
    int n = 0,c;
    while(true){
        c = getchar();
        if(c == 32) break;
        else {
            s[n] = c;
            n++;
        }
    }
    scanf("%d %d",&in,&out);
    // переводим в десятичную систему счисления
    unsigned int res10 = 0;
    for(int i = 0; i < n; i++){
        res10 = (res10*in) + char_to_int(s[i]);
    }
    free(s); // добавил очищение выделенной памяти
    interpretation10_to(res10,out);
}

int main() {
    interpretation();
    return 0;
}
