#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXSIZE 200

typedef struct Stack{
        int top;
        char items[];
}STACK;

bool isEmpty(STACK*);
void push(STACK*,char);
char pop(STACK*);
bool isFull(STACK*);
void CreateS(int,STACK*);
void freeStack(STACK*);
int main(void){
    char input[MAXSIZE];

    while(scanf("%s",input)!=EOF){
        int i=0;
        STACK s;
        CreateS(MAXSIZE,&s);
        while(input[i]!='\0'){
            if(input[i]=='('){
                push(&s,'(');
            }else if(input[i]==')'){
                push(&s,'(');
                if(s.items[s.top-1]=='('){
                    pop(&s);
                    pop(&s);
                }
            }
            i++;
        }
        if(isEmpty(&s)){
            printf("1\n");
        }else{
            printf("0\n");
        }
        memset(input,'\0',MAXSIZE);
    }

    return 0;
}

bool isEmpty(STACK *s){
        if(s->top==-1){
            return true;
        }else{
            return false;
        }
}
void push(STACK *s,char x){
    s->items[++s->top]=x;
}
char pop(STACK *s){
        return s->items[s->top--];
}
bool isFull(STACK *s){
     if(s->top==MAXSIZE-1){
            return true;
    }else{
            return false;
    }
}
void CreateS(int i,STACK *s){
    char *c= s->items;
    c= malloc(i*sizeof(char)); // ¢Xt?m¢XO????
    s->top=-1;
}

