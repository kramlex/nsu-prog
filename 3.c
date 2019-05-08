//
// Created by markd on 02.03.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

double f(double x){
    return 414143*x  - 2343234;
    // введите монотонную функцию
    // f(x) = 414143x - 2343234
    // f(x) = 0
    // x ~= 5.658031
}

double findRoot(double a, double b){
    double eps = 1e-6; // погрешность измерения
    double l = a;
    double r = b;
    double m;
    bool up = f(a) <= f(b);
    while (r - l > eps){ // бинпоиск по вещественной монотоной функции
        m = (l+r)/2;
        if((up && f(m) < 0) || (!up && f(m) > 0) )
            l = m;
        else
            r = m;
    }
    return (l+r)/2;
    // так же возвращает правую границу, если на данном промежутке корень не найден
}

int main() {
    double res = findRoot(-1*1e9,1e9);
    printf("%f" ,res);
    return 0;
}