#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#define MAXSIZE 200

typedef struct Stack{
        int top;
        char items[MAXSIZE];
        double items2[MAXSIZE];
}STACK;


void CreateS(int,STACK*);
bool isEmpty(STACK*);
void push(STACK*,char);
char pop(STACK*);
bool isFull(STACK*);
int priorityisp(char);
int priorityicp(char);

void push2(STACK*,double);
double pop2(STACK*);

void toPostifx(char*,char*,int*);
int calPostifx(char*,int*);
void freeStack(STACK *s);

int main(void){
    char input[MAXSIZE];
    int op[MAXSIZE];
    while(scanf("%s",input)!=EOF){
        memset(op,0,MAXSIZE);
        char postfx[MAXSIZE];
        toPostifx(input,postfx,op);
        int anw = calPostifx(postfx,op);
        printf("%d\n",anw);
        memset(input, '\0', MAXSIZE);
        memset(postfx, '\0', MAXSIZE);     
       
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

void push2(STACK *s,double x){
    s->items2[++s->top]=x;
}
double pop2(STACK *s){
    return s->items2[s->top--];

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
    double *a= s->items2;
    c= malloc(i*sizeof(char)); // 
    a= malloc(i*sizeof(double));
    s->top=-1;
}
void freeStack(STACK *s){
    free(s);
}
int priorityisp(char c){
    switch(c){
        case '+': return 12;
        case '-': return 12;
        case '/': return 13;
        case '*': return 13;
        case '\0' : return 0;
        case '(' : return 0;
        case ')' :return 19;
    }
}

int priorityicp(char c){
    switch(c){
        case '+': case '-': return 12;
        case '/': case '*': return 13;
        case '\0' :  return 0;
        case ')' :return 19;
        case '(' : return 20;
        default : return 0;
    }
}

void toPostifx(char* c,char* re,int* op){
    int i=0,now=0,coun=0;
    STACK s;
    CreateS(MAXSIZE,&s);
    while((c[i])!='\0'){
        if(c[i]>='0' && c[i]<='9'){
            re[now] = c[i];
            now++;
        }else{
            if(c[i]=='-'){
                if(c[i-1]!=')'){
                    if((c[i-1]<'0' || c[i-1]>'9') || i==0){
                        op[coun]=1;
                        coun++;    
                    }    
                }
                
            }
            if(s.top==-1){
                push(&s,c[i]);
            }else if(c[i]==')'){
                while(s.items[s.top]!='('){
                    re[now]=pop(&s);
                    now++;
                }
                pop(&s);
            }else{
                while(priorityisp(s.items[s.top])>=priorityicp(c[i]) && s.top!=-1){
                    if(s.items[s.top]=='-'){
                        coun++;
                    }
                    re[now]=pop(&s);
                    now++;
                }
                push(&s,c[i]);    
            }
        }
        i++;
    }

    while(s.top!=-1){
        if(s.items[s.top]=='-'){
            coun++;
        }
        re[now]=pop(&s);
        now++;
    }
    printf("%s\n",re);
    freeStack(&s);
}

int calPostifx(char* c,int* op){
    int i=0,coun=-1;
    STACK s;
    CreateS(MAXSIZE,&s);
    while(c[i]!='\0'){
        if(c[i]>='0' && c[i]<='9'){
            push2(&s,(double)(c[i])-'0');
            //printf("%lf\n",(double)(c[i])-'0');
        }else{
            double ic1=0,ic2=0;
            if(c[i]=='-'){
                coun++;
                if(op[coun]==1){
                        
                        push2(&s,pop2(&s)*(-1));
                    }else{
                        push2(&s,pop2(&s)*(-1)+pop2(&s));
                        //printf("%lf",s.items2[s.top]);   
                    }
            }
            switch(c[i]){
                case '+':
                    ic2=pop2(&s);
                    ic1=pop2(&s);
                    push2(&s,ic2+ic1);
                    break;
                case '*':
                    push2(&s,pop2(&s)*pop2(&s));
                    break;
                case '/':
                    ic2=pop2(&s);
                    ic1=pop2(&s);
                    push2(&s,ic1/ic2);
                    break;
            }
            //printf("%lf\n",s.items2[s.top]);
        }
        i++;
    }
    freeStack(&s);
    //printf("\n%lf\n",s.items2[s.top]);
    if(s.items2[s.top]<0){
        return (int)(pop2(&s)-0.5); 
    }else{
        return (int)(pop2(&s)+0.5); 
    }
   
}

