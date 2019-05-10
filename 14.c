//
// Created by markd on 02.05.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define POINT '.'

void dfs(int x, int y, char *arr, char *used, int n, int m , bool *way){
    if (x == n-1 || y == m-1 || x == 0 || y == 0) *(way) = true;
    else{
        used[x*n+y] = true;
        if(arr[(x+1)*n+y] == POINT && !used[(x+1)*n+y] ) dfs(x+1,y, arr, used , n, m, way);
        if(arr[(x-1)*n+y] == POINT && !used[(x-1)*n+y] ) dfs(x-1,y,arr, used , n, m, way);
        if(arr[x*n+y+1] == POINT && !used[x*n+y+1] ) dfs(x,y+1, arr, used , n, m, way);
        if(arr[x*n+y-1] == POINT && !used[x*n+y-1] ) dfs(x,y-1, arr, used , n, m, way);
    }
}

int main(){
    bool way = false;
    int n,m;
    scanf("%d %d", &n , &m);
    char *arr = malloc(n * m * sizeof(char));
    if(!arr) return 0;
    char *used = malloc(n * m * sizeof(char));
    if(!used) return 0;
    int x,y;
    char buffer[m+1];
    for(int i = 0; i < n; i++){
        scanf("%s",buffer);
        for(int j = 0; j < m; j++){
            arr[i*n+j] = buffer[j];
            if(arr[i*n+j] == 'x'){
                x = i; y = j;
            }
            used[i*n+j] = false;
        }
    }
    dfs(x,y,arr,used,n,m,&way);
    printf(way?"Yes":"No");
    return 0;
}