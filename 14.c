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

bool lol = false;
bool used[1000][1000];
char arr[1000][1000];
int n,m;
int k = 0;

void dfs(int x,int y){
    if (x == n-1 || y == m-1 || x == 0 || y == 0)
        lol = true;
    else{
        used[x][y] = true;
        k++;
        if(arr[x+1][y] == POINT && !used[x+1][y] ) dfs(x+1,y);
        if(arr[x-1][y] == POINT && !used[x-1][y] ) dfs(x-1,y);
        if(arr[x][y+1] == POINT && !used[x][y+1] ) dfs(x,y+1);
        if(arr[x][y-1] == POINT && !used[x][y-1] ) dfs(x,y-1);
    }
}

int main(){
    scanf("%d %d", &n , &m);
    char c;
    int x,y;
    char buffer[m+1];
    for(int i = 0; i < n; i++){
        scanf("%s",buffer);
        for(int j = 0; j < m; j++){
            arr[i][j] = buffer[j];
            if(arr[i][j] == 'x'){
                x = i;
                y = j;
            }
            used[i][j] = false;
        }
    }
    dfs(x,y);
    printf(lol?"Yes":"No");
    printf("% d", k);
    return 0;
}