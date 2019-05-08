//
// Created by markd on 12.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

long long toSingleIndex(long long i , long long j, long long dim){
    return ((i*dim) + j);
}

int main(){
    long long dim1,dim2;
    FILE *matrixA = fopen("A.txt" , "r") , *matrixB = fopen("B.txt" , "r");
    if(!matrixB || !matrixA){
        exit(EXIT_FAILURE);
    }

    fscanf(matrixA,"%lli" , &dim1);
    fscanf(matrixB,"%lli" , &dim2);
//    printf("%lli %lli" , dim1 , dim2);
    assert(dim1 == dim2);

    long long n = dim1; // сравниваем размерности для удобства


    long long *a = (long long *)malloc(n * n * sizeof(long long)) , *b = (long long *)malloc(n * n * sizeof(long long));
    if(!a || !b) exit(EXIT_FAILURE);

    for(long long i = 0; i < n; i++){ // считываем сразу два массива, но из разных файлов
        for(long long  j = 0; j < n ; j++){

            fscanf(matrixA, "%lli" , (a + toSingleIndex(i,j,n) ) );
            fscanf(matrixB, "%lli" , (b + toSingleIndex(i,j,n) ));
        }
    }
    fclose(matrixA); fclose(matrixB);

    FILE *matrixM = fopen("mult.txt", "w");
    if(!matrixM) exit(EXIT_FAILURE);

    // печатаем результат в файл
    fprintf(matrixM,"%lli \n", n);
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            long long mult = 0;
            for(long long k = 0; k < n; k++){
                mult += a[toSingleIndex(i,k,n)] * b[toSingleIndex(k,j,n)];
            }
            fprintf(matrixM, "%lli ", mult);
        }
        fprintf(matrixM,"\n");
    }
    // закрываем файл и чистим память
    free(a);
    free(b);
    fclose(matrixM);
    return 0;
}
