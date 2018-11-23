#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 250

typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    int weight;
    int lens;
    char data[MAXN];
}node;

typedef struct NODE *nodeptr;

int main(){

}