//
// Created by markd on 22.04.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BASE 10
#define MULTI 2
#define DEFAULT_INIT_SIZE 16

typedef struct d_array {
    int *arr;
    size_t size, used;
} d_array;

void free_arr(d_array *a){
    free(a->arr);
    a->used = a->size = 0;
}

bool resize_arr(d_array *a){
    a->size *= MULTI;
    int *pt = a->arr;
    a->arr = realloc(a->arr, a->size * sizeof(int));
    if(!a->arr) {
        free(pt);
        return false;
    }
    return true;
}

bool init_arr(d_array *a, size_t init_size){
    a->arr = malloc(init_size * sizeof(int));
    if(!a->arr) return false;
    a->used = 0;
    a->size = init_size;
    return true;
}

bool push(d_array *a, int key){
    if(a->used == a->size) if(!resize_arr(a)) return false;
    a->arr[a->used++] = key;
    return true;
}



void printBigInt(d_array *a) {
    for (int i = a->used - 1; i >= 0; i--) {
        printf("%d", a->arr[i]);
    }
}

bool mulBigInt(d_array *a, int m) {
    for (int j = 0; j < a->used; j++)
        a->arr[j] *= m;

    for (int j = 0; j < a->used - 1; j++)
        if (a->arr[j] >= BASE) {
            a->arr[j+1] += a->arr[j] / BASE;
            a->arr[j] %= BASE;
        }
    while (a->arr[a->used - 1] >= BASE) {
        if (!push(a, a->arr[a->used - 1] / BASE))
            return false;
        a->arr[a->used - 2] %= BASE;
    }
    return true;
}


// n! ~ sqrt(2*p*n) * (n/e)^n
// пусть sqrt(2*p*n) * (n/e)^n = ST
// тогда n! ~ ST
// Получаем примерную длинну факториала
// ceil(log10(ST + 0.5)) = len
// Тогда имеем оценку сверху работы программы O(len * n) ~ O(ceil(log10( sqrt(2*p*n) * (n/e)^n )) * n)
// На самом деле программа работает чуть быстрее т.к длина факториала является переменной величиной во время работы программы


int main() {
    d_array arr;
    if (init_arr(&arr, DEFAULT_INIT_SIZE)) {
        push(&arr, 1);

        int n;
        scanf("%d", &n);
        for (int i = 2; i <= n; i++) {
            if (!mulBigInt(&arr, i)) exit(EXIT_FAILURE);
        }
        printBigInt(&arr);

        free_arr(&arr);
        exit(EXIT_SUCCESS);
    }
    else {
        exit(EXIT_FAILURE);
    }
}