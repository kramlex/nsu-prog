//
// Created by markd on 02.05.2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define USE_MERGE_SORT true
#define DEFAULT_INIT_SIZE 16
#define MULTI_P 2

typedef struct {
    char* name;
    double x;
    double y;
    double res;
    int count;
} member;

typedef struct{
    member *arr;
    size_t used;
    size_t size;
} members;

bool init_arr(members *a , size_t init_size){
    a->arr = malloc(init_size * sizeof(member));
    if(!a->arr) return false;
    a->used = 0;
    a->size = init_size;
    return true;
}

bool resize(members *a){
    a->size *= MULTI_P;
    member *pt = a->arr;
    a->arr = realloc(a->arr, a->size * sizeof(member));
    if(!a->arr) {
        free(pt);
        return false;
    }
    return true;
}

bool push(members *a,  member key){
    if(a->used == a->size) if(!resize(a)) return false;
    a->arr[a->used++] = key;
    return true;
}

void free_arr(members *a){
    free(a->arr);
    a->used = a->size = 0;
}

// СОРТИРОВКИ

bool merge(member *arr, size_t l, size_t m, size_t r , bool (*cmp)(member,member) ){
    size_t i, j, k;
    size_t n1 = m - l + 1; // размеры подмассивов
    size_t n2 =  r - m;

    member *l_buff = malloc(sizeof(member) * n1);
    member *r_buff = malloc(sizeof(member) * n2);
    if(!l_buff || !r_buff) return false;

    for (i = 0; i < n1; i++)
        l_buff[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        r_buff[j] = arr[m + 1+ j];
    i = j = 0;
    k = l;
    while (i < n1 && j < n2){
        if ( cmp(l_buff[i],r_buff[j]) ){
            arr[k] = l_buff[i];
            i++;
        }
        else{
            arr[k] = r_buff[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = l_buff[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = r_buff[j];
        j++;
        k++;
    }
    free(l_buff);
    free(r_buff);
    return true;
}
// сортирова слиянием
bool merge_sort(member *arr, size_t l, size_t r , bool (*cmp)(member,member)){
    if (l < r){
        size_t m = l+(r-l)/2;
        if(!merge_sort(arr, l, m , cmp) || !merge_sort(arr, m+1, r , cmp) || !merge(arr, l, m, r , cmp)) return false;
    }
    return true;
}

bool cmp1(member x, member y){
    return (strcmp(x.name,y.name) <= 0);
}

bool cmp2 (member x , member y){
    return (x.res == y .res ? cmp1(x,y) : (x.res <= y.res));
}

void q_sort (member *a, int l, int r, bool (*cmp)(member,member) ){
    int i, j;
    member x, buf;
    i = l;
    j = r;
    x = a[l + rand()%(r - l + 1)];
    do{
        while (cmp(a[i],x))
            i++;
        while (cmp(x,a[j]))
            j--;
        if (i <= j){
            buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
    } while( i <= j);

    if (l < j) q_sort (a, l, j, cmp );
    if (r > i) q_sort (a, i, r , cmp );
}


//
double calc_distance(double x, double y){
    return sqrt(x*x + y*y);
}


bool read_members(members *all){
    double x,y;
    bool check = true;
    while(check){
        char c;
        while(check){
            c = getchar();
            if(c == '\n' ) check = false;
            if(c == '\"') break;
        }
        if(!check) break;
        member new_member;
        new_member.name = malloc(51* sizeof(char));
        if(!new_member.name) return false;
        scanf("%[^\"]%*c %lf %lf", new_member.name,&new_member.x,&new_member.y);
        new_member.count = 1;
        new_member.res = calc_distance(new_member.x,new_member.y);
        if(!push(all,new_member)) return false;
        while(true){
            c = getchar();
            if(c == '\n' ) break;
        }
    }
    return true;
}


bool merge_members(members *all, members *set){
    member new_member = all->arr[0];
    if(all->used == 1){
        if(!push(set,new_member)) return false;
        return true;
    }
    for(size_t i = 1; i < all->used; i++){
        if(!strcmp(all->arr[i].name, new_member.name)){
            new_member.res += all->arr[i].res;
            new_member.count++;
        }
        else{
            new_member.res /= new_member.count;
            new_member.res = (new_member.res * 100);
            new_member.res = (int) new_member.res;
            if(!push(set, new_member)) return false;
            new_member = all->arr[i];
        }
        if(i == all->used-1 ){
            new_member.res /= new_member.count;
            new_member.res = (new_member.res * 100);
            new_member.res = (int) new_member.res;
            if(!push(set,new_member)) return false;
        }
    }
    return true;
}

int main(){
    members all;
    if(!init_arr(&all,DEFAULT_INIT_SIZE) || !read_members(&all)){
        free_arr(&all);
        return 0;
    }
    // сортировка в лексикографическом порядке
    if(USE_MERGE_SORT) {
        if(!merge_sort(all.arr , 0 , all.used-1 , cmp1)){
            free_arr(&all);
            return 0;
        }
    }
    else
        q_sort(all.arr, 0, all.used-1 , cmp1);

    for(size_t i = 0; i < all.used; i++)
        printf("\"%s\" \n",all.arr[i].name);

    printf("\n");

    members set;
    if(!init_arr(&set,DEFAULT_INIT_SIZE) || !merge_members(&all,&set)){
        free_arr(&all);
        free_arr(&set);
        return 0;
    }
    free_arr(&all);

    printf("\n");
    for(size_t i = 0; i < set.used; i++)
        printf("\"%s\" \n",set.arr[i].name);

    printf("\n");

    // сортировка по res
    if(USE_MERGE_SORT) {
        if(!merge_sort(set.arr , 0 , set.used-1 , cmp2)){
            free_arr(&set);
            return 0;
        }
    }
    else
        q_sort(set.arr, 0, set.used-1 , cmp2);

    for(size_t i = 0; i < set.used; i++)
        printf("\"%s\" \n",set.arr[i].name);
    free_arr(&set);

    return 0;
}
