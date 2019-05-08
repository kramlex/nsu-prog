//
// Created by markd on 12.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Стандартный алгоритм бин-поиска
 * @param arg - искомый эл-т
 * @param arr - массив для поиска(упорядоченный по условию)
 * @param arr_size - размер данного массива
 * @return true, если arg находится в массиве arr  ; false, если arg нет в массиве arr
 */


bool bin_search(long arg ,long *arr, int arr_size){
    int l, r, m;
    l = 0;
    r = arr_size - 1;
    while (l <= r){
        m = (l + r) / 2;
        if (arg < arr[m]) r = m - 1;
        else if (arg > arr[m]) l = m + 1;
        else return true;
    }
    return false;
}

int main(){
    long n,k,z;
    scanf("%ld", &n); //array size

    long *a = (long*)malloc(n*sizeof(long));
    if(!a) exit(EXIT_FAILURE)


    for(int i = 0; i < n; i++)
        scanf("%li", (a+i) );

    scanf("%ld",&k);

    for(int i = 0; i < k; i++){
        scanf("%ld", &z);
        printf("%s" , bin_search(z,a,n) ? "Exists\n" : "Absent\n");
    }
    free(a);
    return 0;
}