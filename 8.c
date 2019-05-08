//
// Created by markd on 12.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
/**
 * считаем кол-во слов в fileName
 * @param fileName - название файла с расщирением в котором будем считать слова
 * @return words_counter - кол-во слов
 */
unsigned long long words_counter(char* fileName){ // принимает строку - название файла
    FILE *input = fopen(fileName, "r");
    if(!input) exit(EXIT_FAILURE);

    unsigned long long words_count = 0;
    char c;
    bool space = true; // проверка на пробелы

    while(!feof(input) ){ // идем до конца файла
        c = fgetc(input);
        if(isspace(c) || c == EOF){
            space = true;
        }
        else{
            if(space) {
                words_count++;
            }
            space = false;
        }
    }
    fclose(input);
    return words_count; // возвращаем кол-во слов
}

int main(int argc, char ** argv){
    assert(argc == 2);
    printf("%llu", words_counter(argv[1]) );
    return 0;
}
