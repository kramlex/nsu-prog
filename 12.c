//
// Created by markd on 16.04.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define STR_REV "Revision"
#define STR_OPEN "Open"
#define STR_ADD "Add"
#define STR_CLOSE "Close"
#define STR_ALL "all"
#define STR_END "End"

// реализовано АВЛ дерево с операциями
// добавление(создание), удаление, поиск - все операции работают за O(log n)
// расход памяти O(n * sizeof(node)) ~ O(n)

// программу завершается при вводе слова "End"


typedef struct node{
    unsigned int key;
    unsigned int val;
    struct node *left,*right;
    unsigned int ht;
}node;


node *insert(node *, unsigned int , unsigned int );
node *delete(node *,unsigned int);
int height( node *);
node *rotate_right(node *);
node *rotate_left(node *);
node *right_right_rotation(node *);
node *left_left_rotation(node *);
node *left_right_rotation(node *);
node *right_left_rotation(node *);
int balance_dif(node *);
unsigned int all_bus(node *);
unsigned int bus_for_num(node * , unsigned int);

node * insert(node *root,unsigned int key, unsigned int val ){
    if(root==NULL){ // создание эл-та
        root = (node*)malloc(sizeof(node))
        root->key = key;
        root->val = val;
        root->left = root->right = NULL;
    }
    else if(key > root->key){ // правое поддерево
        root->right=insert(root->right,key,val);
        if(balance_dif(root)==-2) // балансировка
            if(key > root->right->key)
                root=right_right_rotation(root);
            else
                root=right_left_rotation(root);
    }
    else if(key < root->key){ // левое поддерево
        root->left=insert(root->left,key,val);
        if(balance_dif(root) == 2)
            if(key < root->left->key)
                root = left_left_rotation(root);
            else
                root = left_right_rotation(root);
    }
    else if (key == root->key){
        root->val += val; // для операции Add
    }

    root->ht = height(root);
    return root;
}

node * delete(node *root,unsigned int key){
    node *p;
    if(!root)
        return root;
    else if(key > root->key){
        root->right = delete(root->right,key);
        if(balance_dif(root) == 2)
            if(balance_dif(root->left) >= 0)
                root = left_left_rotation(root);
            else
                root = left_right_rotation(root);
    }
    else if(key < root->key){
        root->left = delete(root->left,key);
        if(balance_dif(root) == -2)
            if(balance_dif(root->right) <= 0)
                root = right_right_rotation(root);
            else
                root = right_left_rotation(root);
    }
    else {
        node *pt = root;
        if ( root->left != NULL && root->right != NULL ) {
            p = root->right;
            if(root != NULL){
                while(root->left){
                    p = root;
                    root = root->left;
                }
                p->left = root->right;
                root->right = pt->right;
            }
            root->left = pt->left;
        }
        else if (root->left)
            root = root->left;
        else
            root = root->right;
        if(balance_dif(root) == 2) //балансировка
            if(balance_dif(root->left) >= 0)
                root = left_left_rotation(root);
            else
                root = left_right_rotation(root);
        free(pt);
    }
    return root;
}
// высота
int height(node *root){
    int lh,rh;
    if(root == NULL)
        return 0;
    if(root->left == NULL)
        lh=0;
    else
        lh = 1 + root->left->ht;
    if(root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    if(lh > rh)
        return lh;
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
// левый поворот
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
    int lh,rh;
    if(root==NULL)
        return 0;
    if(root->left==NULL)
        lh=0;
    else
        lh = 1 + root->left->ht;
    if(root->right == NULL)
        rh=0;
    else
        rh = 1 + root->right->ht;
    return lh-rh;
}

unsigned int all_bus(node *root){
    if(root == NULL)
        return 0;
    else return root->val + all_bus(root->left) + all_bus(root->right);
}

unsigned int bus_for_num(node * root, unsigned int key){
    if(root != NULL){
        if(root->key == key)
            return root->val;
        if(root->key > key)
            return bus_for_num(root->left,key);
        else
            return bus_for_num(root->right, key);
    }
    return 0;
}

void free_tree(node *root){
    if(root != NULL){
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}


int main() {
    node *root=NULL;

    while(true){
        char *str1 = malloc(11 * sizeof(char));
        char *str2 = malloc(11 * sizeof(char));
        if(!str1 || !str2){
            printf("Memory error");
            free_tree(root);
            break;
        }
        char c;
        scanf("%s",str1);
        // REVISION
        if(!strcmp(str1,STR_REV)){
            scanf("%s", str2);
            if( !strcmp(str2,STR_ALL) ){
                unsigned int all = all_bus(root);
                printf("%u\n",all);
            }
            else{
                unsigned int key = atoi(str2);
                unsigned int count = bus_for_num(root,key);
                if(count) printf("%u\n",count);
                else printf("No route\n");
            }
        }
        else if( !strcmp(str1,STR_END) ){
            free_tree(root);
            break;
        }
        //OPEN
        else if( !strcmp(str1,STR_OPEN) ){
            unsigned int key,value;
            scanf("%u %u", &key, &value);
            root = insert(root,key,value);
        }
        //ADD
        else if( !strcmp(str1,STR_ADD) ){
            unsigned int key,value;
            scanf("%u %u", &key, &value);
            root = insert(root, key, value);
        }
        //CLOSE
        else if( !strcmp(str1,STR_CLOSE) ){
            unsigned int key;
            scanf("%u",&key);
            root = delete(root,key);
        }
        while(true){
            c = getchar();
            if(c == '\n')
                break;
        }
    }
}





