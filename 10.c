//
// Created by markd on 06.04.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define MULTI_P 2
#define ENDSTR '\0'
#define DEFAULT_INIT_SIZE 16

typedef struct array_char{
    char *arr;
    size_t size;
    size_t used;
} array_char;

typedef struct node{
    array_char word;
    struct node *next;
} node;

typedef struct stack{
    node *root;
} stack;

void free_arr(array_char *a){
    free(a->arr);
    a->used = a->size = 0;
}

bool resize_arr(array_char *a){
    a->size *= MULTI_P;
    char *pt = a->arr;
    a->arr = realloc(a->arr, a->size * sizeof(char));
    if(!a->arr) {
        free(pt);
        return false;
    }
    return true;
}

bool init_arr(array_char *a, size_t init_size){
    a->arr = malloc(init_size * sizeof(char));
    if(!a->arr) return false;
    a->used = 0;
    a->size = init_size;
    return true;
}

bool push_c(array_char *a,  char key){
    if(a->used == a->size) if(!resize_arr(a)) return false;
    a->arr[a->used++] = key;
    return true;
}

bool push(stack *a, array_char word){
    node *pt = malloc(sizeof(node));
    if(!pt) return false;
    pt->word = word;
    pt->next = a->root;
    a->root = pt;
    return true;
}

void delete_last(stack *a){
    node *pt = a->root;
    a->root = a->root->next;
    free_arr(&pt->word);
    free(pt);
}

void free_stack(stack *a){
    while(a->root != NULL) delete_last(a);
}

void all_free(stack *s, array_char *a){
    free_stack(s);
    free_arr(a);
}

// *************************

bool PrintWordsReverse(char* fileName){
    FILE* input = fopen(fileName, "r");
    if(!input){
        fclose(input);
        return false;
    }

    bool space = true;
    char c;
    stack words;
    words.root = NULL;
    array_char new_word;
    while(!feof(input)){
        c = fgetc(input);
        if(isspace(c) || c == EOF){
            if(!space ){
                if(!push_c(&new_word, ENDSTR)){
                    all_free(&words,&new_word);
                    return false;
                }
                if(!push(&words,new_word)){
                    all_free(&words,&new_word);
                    return false;
                }
            }
            space = true;
            continue;
        }
        else{
            if(space){
                if(!init_arr(&new_word , DEFAULT_INIT_SIZE)){
                    all_free(&words,&new_word);
                    return false;
                }
            }
            space = false;
            if(!push_c(&new_word,c)){
                all_free(&words,&new_word);
                return false;
            }
        }
    }
    fclose(input);
    while(words.root != NULL){
        printf("%s ", words.root->word.arr);
        delete_last(&words);
    }
    return true;
}

int main(int argc, char ** argv){
    if(argc == 1){
        printf("Enter file name");
    }
    else if(!PrintWordsReverse(argv[1])){
        printf("MEMORY ERROR");
    }
    return 0;
}
