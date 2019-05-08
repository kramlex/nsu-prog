//
// Created by markd on 05.05.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define COS_STR "cos"
#define SIN_STR "sin"
#define SQRT_STR "sqrt"
#define ADD_STR "+"
#define SUB_STR "-"
#define MULT_STR "*"
#define DIV_STR "/"
#define VAR_STR "x"

typedef struct constant constant;
typedef struct variable variable;
typedef struct binary binary;
typedef struct unary unary;
typedef struct expression expression;
typedef struct node node;
typedef struct stack stack;

struct constant{
    int val;
};

struct binary{
    char name[15];
    expression *left_exp;
    expression *right_exp;
};

struct unary{
    char name[15];
    expression *exp;
};

struct variable{
    char name[15];
};

struct expression{
    // 0 - var
    // 1 - const
    // 2 - bin
    // 3 - unary
    int type;
    union{
        variable v;
        constant c;
        binary b;
        unary u;
    };
};

struct node{
    expression *exp;
    node *next;
};

struct stack{
    node *root;
};

bool push(stack *a, expression *exp) {
    node *pt = malloc(sizeof(node));
    if (!pt) return false;
    pt->exp = exp;
    pt->next = a->root;
    a->root = pt;
    return true;
}

node *pop(stack *a){
    node *pt = a->root;
    a->root = a->root->next;
    return pt;
}

void free_tree(expression *a){
    if(a->type == 2){
        if(!a->b.left_exp)
            free_tree(a->b.left_exp);
        if(!a->b.right_exp)
            free_tree(a->b.right_exp);
    }
    if(a->type == 1)
        free_tree(a->u.exp);
    free(a);
}

void free_stack(stack *a){
    while(a->root != NULL){
        node *pt = pop(a);
        free(pt->exp);
        free(pt);
    }
}

bool create_tree(stack *operation){
    char buff[15];
    expression *new;
    while(scanf("%s",buff)){
        if(!strcmp(buff,".")) break;
        new = malloc(sizeof(expression));
        // VAR (0)
        if(!strcmp(buff,VAR_STR)){
            new->type = 0;
            strcpy(new->u.name,buff);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }

        // UNARY(3)
        else if(!strcmp(buff,COS_STR)){
            new->type = 3;
            node *pt = pop(operation);
            strcpy(new->u.name,buff);
            new->u.exp = pt->exp;
            free(pt);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }
        else if(!strcmp(buff,SIN_STR)){
            new->type = 3;
            node *pt = pop(operation);
            strcpy(new->u.name,buff);
            new->u.exp = pt->exp;
            free(pt);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }
        else if(!strcmp(buff,SQRT_STR)){
            new->type = 3;
            node *pt = pop(operation);
            strcpy(new->u.name,buff);
            new->u.exp = pt->exp;
            free(pt);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }

        // BINARY (2)
        else if(!strcmp(buff,SUB_STR)){
            new->type = 2;
            node *pt1 = pop(operation);
            node *pt2 = pop(operation);
            strcpy(new->b.name,buff);
            new->b.left_exp = pt2->exp;
            new->b.right_exp = pt1->exp;
            free(pt1);
            free(pt2);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }
        else if(!strcmp(buff,MULT_STR)){
            new->type = 2;
            node *pt1 = pop(operation);
            node *pt2 = pop(operation);
            strcpy(new->b.name,buff);
            new->b.left_exp = pt2->exp;
            new->b.right_exp = pt1->exp;
            free(pt1);
            free(pt2);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }
        else if(!strcmp(buff,DIV_STR)){
            new->type = 2;
            node *pt1 = pop(operation);
            node *pt2 = pop(operation);
            strcpy(new->b.name,buff);
            new->b.left_exp = pt2->exp;
            new->b.right_exp = pt1->exp;
            free(pt1);
            free(pt2);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }
        else if(!strcmp(buff,ADD_STR)){
            new->type = 2;
            node *pt1 = pop(operation);
            node *pt2 = pop(operation);
            strcpy(new->b.name,buff);
            new->b.left_exp = pt2->exp;
            new->b.right_exp = pt1->exp;
            free(pt1);
            free(pt2);
            if(!push(operation, new)) {
                free(new);
                return false;
            }
        }

        // CONST (1)
        else{
            new->type = 1;
            new->c.val = atoi(buff);
            if(!push(operation, new)){
                free(new);
                return false;
            }
        }
//        printf("\npush %s\n", buff);
    }
    return true;
}

void infix_print(expression *root){
    if(root->type == 0)
        printf("%s",root->v.name);
    if(root->type == 1)
        printf("%d", root->c.val);
    if(root->type == 2){
        printf(root->b.left_exp->type == 1 || root->b.left_exp->type == 0 ? "" : "(");
        infix_print(root->b.left_exp);
        printf(root->b.left_exp->type == 1 || root->b.left_exp->type == 0 ? "" : ")");
        printf(" %s ",root->b.name);
        printf(root->b.right_exp->type == 1 || root->b.right_exp->type == 0 ? "" : "(");
        infix_print(root->b.right_exp);
        printf(root->b.right_exp->type == 1 || root->b.right_exp->type == 0 ? "" : ")");
    }
    if(root->type == 3){
        printf("%s",root->u.name);
        printf("(");
        infix_print(root->u.exp);
        printf(")");
    }
}

void differ(expression *root){
    // BIN
    if(root->type == 2){
        printf("(");
        // + or -
        if(!strcmp(root->b.name,SUB_STR) || !strcmp(root->b.name,ADD_STR)){
            differ(root->b.left_exp);
            printf(" %s ",root->b.name);
            differ(root->b.right_exp);
        }
        // /
        else if(!strcmp(root->b.name,DIV_STR)){
            printf("(");
            differ(root->b.left_exp);
            printf(")");
            printf(" %s ",MULT_STR);
            printf("(");
            infix_print(root->b.right_exp);
            printf(")");
            printf(" %s ",SUB_STR);

            printf("(");
            infix_print(root->b.left_exp);
            printf(")");
            printf(" %s ",MULT_STR);
            printf("(");
            differ(root->b.right_exp);
            printf(")");
            printf(")");

            printf(" %s ",DIV_STR);
            printf("((");
            infix_print(root->b.right_exp);
            printf(")");
            printf(" %s ",MULT_STR);
            printf("(");
            infix_print(root->b.right_exp);
            printf("))");
        }
        // *
        else if(!strcmp(root->b.name,MULT_STR)){
            printf("(");
            differ(root->b.left_exp);
            printf(" %s ",MULT_STR);
            infix_print(root->b.right_exp);
            printf(")");

            printf(" %s ",ADD_STR);

            printf("(");
            infix_print(root->b.left_exp);
            printf(" %s ",MULT_STR);
            differ(root->b.right_exp);
            printf(")");
        }
        printf(")");
    }
    // UNAR
    if(root->type == 3){
        printf("(");
        // sin
        if(!strcmp(root->b.name,SIN_STR)){
            printf("%s",COS_STR);
            printf("(");
            infix_print(root->u.exp);
            printf(")");
            printf(" %s ",MULT_STR);
            differ(root->u.exp);
        }
        // cos
        else if(!strcmp(root->b.name,COS_STR)){
            printf("-1 * %s",SIN_STR);
            printf("(");
            infix_print(root->u.exp);
            printf(")");
            printf(" %s ",MULT_STR);
            differ(root->u.exp);
        }
        // sqrt
        else if(!strcmp(root->b.name,SQRT_STR)){
            printf("(");
            printf("1 / (2 * sqrt(");
            infix_print(root->u.exp);
            printf(")))");
            printf(" %s ",MULT_STR);
            differ(root->u.exp);
        }
        printf(")");
    }
    // VAR
    if(root->type == 0)
        printf("1");
    // CONST
    if(root->type == 1)
        printf("0");
}

int main(){
    stack operations;
    if(!create_tree(&operations)){
        free_stack(&operations);
        printf("MEMORY ERROR");
        return 0;
    }
    expression *tree = operations.root->exp;
    differ(tree);
    free_tree(tree);
    return 0;
}