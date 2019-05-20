#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_SIZE 1000
#define POINT '.'

typedef struct queue queue;
typedef struct node node;
typedef struct pair pair;

bool visited[MAX_SIZE][MAX_SIZE];
char graph[MAX_SIZE][MAX_SIZE];

struct pair{
    int x;
    int y;
};
struct node {
    node *next;
    pair val;
};
struct queue {
    node *front;
    node *rear;
    int size;
};

bool push(queue *q, pair x) {
    node *p = malloc(sizeof(node));
    if (!p) return false;
    p->val = x;
    if (!q->size) q->front = p;
    else {
        q->rear->next = p;
        if (q->size == 1)
            q->front->next = p;
    }
    q->rear = p;
    q->size++;
    return true;
}

pair pop(queue *q) {
    assert(q->front != NULL);
    pair r = q->front->val;
    node *front = q->front;
    q->front = q->front->next;
    q->size--;
    free(front);
    return r;
}

void free_queue(queue *q) {
    assert(q != NULL);
    while (q->size)
        pop(q);
}

bool bfs_step(int x, int y, queue *grey, int n, int m) {
    if(graph[x][y] == POINT && !visited[x][y] ){
        if (!push(grey, (pair) {x, y}))
            return false;
        visited[x][y] = true;
    }
    return true;
}

int bfs(pair start, int n, int m) {
    queue *grey = &(queue) {NULL, NULL, 0};
    if (!push(grey, start))
        return -1;
    visited[start.x][start.y] = true;
    while (grey->size) {
        pair first = pop(grey);
        printf("(%d , %d) \n", first.x , first.y);
        if (first.x == n - 1 || first.y == m - 1 || first.x == 0 || first.y == 0) {
            free_queue(grey);
            return 1;
        }
        if (!bfs_step( first.x + 1, first.y, grey, n, m) ||
            !bfs_step( first.x - 1, first.y, grey, n, m) ||
            !bfs_step( first.x, first.y - 1, grey, n, m) ||
            !bfs_step( first.x, first.y + 1, grey, n, m)) {
            free_queue(grey);
            return -1;
        }
    }
    return 0;
}

int main() {
    pair start;
    int n, m;
    scanf("%d%d", &n, &m);
    if(n > MAX_SIZE && m > MAX_SIZE & n < 0 && m < 0) {
        printf("invalid value");
        return 0;
    }
    getchar();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%c", &graph[i][j]);
            if (j == m - 1)
                getchar();
            if (graph[i][j] == 'x'){
                start = (pair) {i,j};
            }
        }
    }
    int ans = bfs(start, n, m);
    printf(ans == -1? "out of memory": (ans ? "Yes" : "No"));
}