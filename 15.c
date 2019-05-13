//
// Created by markd on 18.04.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MULTI 2
#define DEFAULT_INIT_SIZE 16
#define INF 1000000000
#define FILENAME "distances.txt"


// **************************************************
// PAIR

typedef struct pair {
    char first[100];
    long second;
} pair;

// **************************************************

// **************************************************
// PAIR ARRAY

typedef struct pair_array{
    pair *arr;
    size_t used , size;
} pair_array;

void free_pair_array(pair_array *pa){
    free(pa->arr);
    pa->used = pa->size = 0;
}

bool resize_pair_array(pair_array *pa){
    pa->size *= MULTI;
    pair *pt = pa->arr;
    pa->arr = realloc(pa->arr, pa->size * sizeof(pair));
    if(!pa->arr){
        free(pt);
        return false;
    }
    return true;
}

bool init_pair_array(pair_array *pa, size_t init_size){
    pa->arr = malloc(init_size * sizeof(pair));
    if(!pa->arr) return false;
    pa->used = 0;
    pa->size = init_size;
    return true;
}

bool push_pair(pair_array *pa, pair key){
    if(pa->used == pa->size) if(!resize_pair_array(pa)) return false;
    pa->arr[pa->used++] = key;
    return true;
}

// **************************************************
// АВЛ-ДЕРЕВО
typedef struct node node;
node *insert(node *, char[], long *, bool *);
unsigned long height( node *);
node *rotate_right(node *);
node *rotate_left(node *);
node *right_right_rotation(node *);
node *left_left_rotation(node *);
node *left_right_rotation(node *);
node *right_left_rotation(node *);
int balance_dif(node *);

struct node{
    char key[100];
    pair_array arr;
    long i;
    struct node *left,*right;
    unsigned long ht;
};

node * insert(node *root, char key[], long *n , bool *er){
    if(!root){ // создание эл-та
        root = malloc(sizeof(node));
        if(!root){
            *(er) = false;
            return root;
        }
        strcpy(root->key,key);
        if(!init_pair_array(&root->arr,DEFAULT_INIT_SIZE)){
            *(er) = false;
            return root;
        }
        (*n)++;
        root->left = root->right = NULL;
    }
    else if(strcmp(key,root->key) > 0){ // правое поддерево
        root->right=insert(root->right,key,n,er);
        if(balance_dif(root)==-2){
            if(strcmp(key,root->right->key) > 0 ) root=right_right_rotation(root);
            else root=right_left_rotation(root);
        }
    }
    else if(strcmp(key,root->key) < 0 ){ // левое поддерево
        root->left=insert(root->left,key,n,er);
        if(balance_dif(root) == 2){
            if(strcmp(key,root->left->key) < 0) root = left_left_rotation(root);
            else root = left_right_rotation(root);
        }
    }
    root->ht = height(root);
    return root;
}

bool add(node *root, char key[], pair val){
    if(root){
        if(!strcmp(root->key,key)){
            if(!push_pair(&root->arr,val)) return false;
            return true;
        }
        if(strcmp(root->key,key) < 0)
            return add(root->right, key, val);
        else
            return add(root->left, key, val);
    }
    else return false;
}

unsigned long height(node *root){
    unsigned int lh,rh;
    if(!root) return 0;
    if(!root->left) lh=0;
    else lh = 1 + root->left->ht;
    if(!root->right)rh = 0;
    else rh = 1 + root->right->ht;
    if(lh > rh) return lh;
    return rh;
}

node *rotate_right(node *root){
    node *y;
    y = root->left;
    root->left = y->right;
    y->right = root;
    root->ht = height(root);
    y->ht = height(y);
    return y;
}

node *rotate_left(node *root){
    node *y;
    y = root->right;
    root->right = y->left;
    y->left = root;
    root->ht = height(root);
    y->ht = height(y);
    return y;
}

node *right_right_rotation(node *root){
    root = rotate_left(root);
    return root;
}
// правый поворот
node *left_left_rotation(node *root){
    root = rotate_right(root);
    return root;
}

node *left_right_rotation(node *root){
    root->left = rotate_left(root->left);
    root=rotate_right(root);
    return root;
}

node * right_left_rotation(node *root){
    root->right = rotate_right(root->right);
    root=rotate_left(root);
    return root;
}

int balance_dif(node *root){
    long lh,rh;
    if(!root) return 0;
    if(!root->left) lh=0;
    else lh = 1 + root->left->ht;
    if(!root->right) rh=0;
    else rh = 1 + root->right->ht;
    return lh-rh;
}

void free_tree(node *root){
    if(root){
        free_tree(root->left);
        free_tree(root->right);
        free_pair_array(&root->arr);
        free(root);
    }
}

void infix_indexing(node *root, long *i ,char *s1 , char *s2, long *indx1 , long *indx2 , pair_array *pa ){
    if(root){
        infix_indexing(root->left, i, s1, s2, indx1 , indx2 , pa);
        root->i = *i;
        pa[*(i)] = root->arr;
        if(!strcmp(root->key,s1)) *indx1 = *i;
        if(!strcmp(root->key,s2)) *indx2 = *i;
        (*i)++;
        infix_indexing(root->right,i, s1, s2, indx1 , indx2 , pa);
    }
}

long search_index(node * root, char key[]){
    if(root){
        if(!strcmp(root->key,key))
            return root->i;
        else if(strcmp(key,root->key) > 0)
            return search_index(root->right,key);
        else
            return search_index(root->left, key);
    }
    else return -1;
}

char* search_key(node *root, long index){
    if(root){
        if(index == root->i)
            return root->key;
        else if(index < root->i)
            return search_key(root->left, index);
        else
            return search_key(root->right, index);
    }
    else return NULL;
}

void read_str(FILE *input, char from[], char to[], long* price){
    char c;
    while(!feof(input)){
        c = (char)fgetc(input);
        if(c == '\"') break;
    }
    int i = 0;
    while(!feof(input)){
        c = (char)fgetc(input);
        if(c == '\"') break;
        from[i++] = c;
    }
    from[i] = '\0';
    i = 0;
    while(!feof(input)){
        c = (char)fgetc(input);
        if(c == '\"') break;
    }
    while(!feof(input)){
        c = (char)fgetc(input);
        if(c == '\"') break;
        to[i++] = c;
    }
    to[i] = '\0';
    fscanf(input,"%ld", price);
    while(!feof(input)){
        c = (char)fgetc(input);
        if(c == '\n') break;
    }
}

void from_to_read(char from[] , char to[]){
    char c;
    while(true){
        c = (char)getchar();
        if(c == '\"') break;
    }
    int i = 0;
    while(true){
        c = (char)getchar();
        if(c == '\"') break;
        from[i++] = c;
    }
    from[i] = '\0';
    i = 0;
    while(true){
        c = (char)getchar();
        if(c == '\"') break;
    }
    while(true){
        c = (char)getchar();
        if(c == '\"') break;
        to[i++] = c;
    }
    to[i] = '\0';
}

int main(){
    char from[100], to[100];
    long indx1,indx2; // from, to

    from_to_read(from,to);

    FILE *input = fopen(FILENAME , "r");
    if(!input){
        fclose(input);
        return false;
    }

    node *root = NULL;
    long n = 0;

    while(!feof(input)){
        char from_tmp[100], to_tmp[100];
        long price;
        read_str(input,from_tmp,to_tmp,&price);
        pair new_pair;
        //init
        strcpy(new_pair.first,to_tmp);
        new_pair.second = price;
        bool er = true;
        root = insert(root,from_tmp,&n,&er);
        if(!add(root,from_tmp,new_pair)){
            free_tree(root);
            fclose(input);
            return 0;
        }

        root = insert(root,to_tmp,&n,&er);
        if(!er){
            free_tree(root);
            fclose(input);
            return 0;
        }
    }
    fclose(input);

    long indexing = 0;
    pair_array *g = malloc(n * sizeof(pair_array));
    if(!g){
        free(g); free_tree(root);return 0;
    }
    infix_indexing(root,&indexing,from,to,&indx1,&indx2,g);

    long *d = malloc(n * sizeof(long));
    long *p = malloc(n * sizeof(long));
    char *u = calloc((size_t)n ,sizeof(char));
    if(!d || !p || !u){
        free_tree(root);free(u);free(d);free(p); return 0;
    }
    for(long i = 0; i < n ; i++) d[i] = INF;
    d[indx1] = 0;
    if(!g[indx1].used){
        free_tree(root);free(u);free(d);free(p);
        printf("No route");
        return 0;
    }
    for(long i = 0; i < n; ++i) {
        long v = -1;
        for (long j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if(d[v] == INF) break;
        u[v] = true;
        for(long j = 0; j < g[v].used ; ++j){
            long to = search_index(root,g[v].arr[j].first);
            long len = g[v].arr[j].second;
            if(d[v] + len < d[to]){
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
    free(u);
    if(d[indx2] == INF) {
        printf("No route");
        free_tree(root);
        free(d);
        free(p);
        free(g);
        return 0;
    }
    else{
        printf("%ld \n", d[indx2]);
        long *path = malloc(n * sizeof(long));
        if(!path){
            free(path);free(p); free(d);free_tree(root);
            return 0;
        }
        long i = 0;
        for(long v = indx2; v!=indx1; v=p[v]){
            path[i++] = v;
        }
        path[i] = indx1;
        for(int m = i; m >= 0; m--){
            printf("\"%s\" " , search_key(root,path[m]) );
        }
        free(path);
    }
    free_tree(root);free(d);free(p);free(g);
    return 0;
}

