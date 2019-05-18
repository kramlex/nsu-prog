//
// Created by markd on 12.05.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define POINT '.'

typedef struct node node;
typedef struct queue queue;
typedef struct pair pair;

struct pair{
    int x,y;
};

struct node{
    pair key;
    node *next;
};

struct queue{
    int size;
    node *frnt;
    node *rear;
};

bool init(queue *q) {
    q->frnt = malloc(sizeof(node));
    if(!q->frnt)
        return false;
    q->frnt->next = NULL;
    q->rear = q->frnt;
    q->size = 0;
    return true;
}

bool is_empty(queue *q) {
    return q->size == 0;
}

pair pop(queue *q){
    pair k = q->frnt->next->key;
    node *pt = q->frnt;
    q->frnt = q->frnt->next;
    free(pt);
    q->size--;
    return k;
}
bool push(queue *q , pair key){
    q->rear->next = malloc(sizeof(node));
    if(!q->rear->next)
        return false;
    q->rear = q->rear->next;
    q->rear->key = key;
    q->rear->next = NULL;
    q->size++;
    return true;
}
int size(queue *q){
    return q->size;
}

bool is_goal(int x, int y, int n, int m){
    return (x == n-1 || y == m-1 || x == 0 || y == 0);
}

bool bfs_step(int nx, int ny,int n , int m, char *used, char*arr, queue *q){
    if(arr[nx*n+ny] == POINT && !used[nx*n+ny] ){
        pair k = {nx,ny};
        if(!push(q,k))
            return false;
        used[nx*n+ny] = true;
    }
    return true;
}

void free_queue(queue *q){
    if(q->frnt != NULL){
        node *pt = q->frnt;
        q->frnt = q->frnt->next;
        free(pt);
        free_queue(q);
    }
}

// 0 - NO
// 1 - YES
// -1 - MEMORY ERROR
int bfs(int x , int y , int n, int m, char *arr , char* used){
    queue a;
    pair k = {x,y}; // tmp
    if(!init(&a) || !push(&a,k)){
        free_queue(&a);
        return -1;
    }
    used[x*n + y] = true;
    pair key;
    while(!is_empty(&a)) {
        key = pop(&a);
//        printf("%d %d %d \n", key.x , key.y, is_empty(&a));
        if (is_goal(key.x, key.y, n, m)) return 1;
        if(!bfs_step(key.x + 1, key.y,n,m, used, arr, &a)
        || !bfs_step(key.x - 1, key.y,n,m, used, arr, &a)
        || !bfs_step(key.x, key.y + 1,n,m, used, arr, &a)
        || !bfs_step(key.x, key.y - 1,n,m, used, arr, &a))
        {
            free_queue(&a);
            return -1;
        }
    }
    return 0;
}

int main(){
    int n,m;
    scanf("%d %d", &n , &m);
    char *arr = malloc(n * m * sizeof(char));
    if(!arr) return 0;
    char *used = malloc(n * m * sizeof(char));
    if(!used) {
        free(arr);
        return 0;
    }
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

    int ans = bfs(x,y,n,m,arr,used);
    free(arr);
    free(used);
    if(ans == -1){
        printf("MEMORY ERROR");
        return 0;
    }
    else printf(ans ? "Yes" : "No");
    return 0;
}

