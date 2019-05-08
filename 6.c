//
// Created by markd on 12.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

int main(){
    char *str = (char*)malloc(1000*sizeof(char));
    if(!str){
        exit(EXIT_FAILURE);
    }

    int size = 0 , c;

    while(true){
        c = getchar();
        if(c == '\n'){
            break;
        }
        str[size] = c;
        size++;
    }

    bool isPalindrome = true;
    for(size_t j = 0, k = size-1 ; (size % 2) ?  (j != k) : (j!= k+1) ; ) { // цикл идет сразу по двум элементам массива(с конца и начала)
        if(str[j] != str[k]){
            isPalindrome = false;
            break;
        }
        j++;
        k--;
    }

    free(str);

    if(isPalindrome) printf("Yes");
    else printf("No");

    return 0;
}
