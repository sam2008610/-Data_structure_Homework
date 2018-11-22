#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define MAXSIZE 200

struct NODE
{
    int degree;
    int coeff;
    struct NODE* next;
};
typedef struct NODE node;

//calucate function
void getCoef(char*,node**);
void polyAdd(node*,node*,node**);
void polySub(node*,node*,node**);
void polyMul(node*,node*,node**);
//linked-list 
node* getnode(void);
int listEmpty(node*);
void freeptr(node*);
void listadd(node**,int,int);
void listShow(node*);
void freeList(node*);
//others
int COMPARE(int,int);

int main(void)
{
    char input1[MAXSIZE],input2[MAXSIZE];
    while(scanf("%s%s",input1,input2)!=EOF)
    {
        node *ptr1=NULL,*ptr2=NULL,*ptradd=NULL,*ptrsub=NULL,*ptrmul=NULL;
        getCoef(input1,&ptr1);
        getCoef(input2,&ptr2);
        //listShow(ptr2);
        //listShow(ptr1);
        polyAdd(ptr1,ptr2,&ptradd);
        listShow(ptradd);
        polySub(ptr1,ptr2,&ptrsub);
        listShow(ptrsub);
        polyMul(ptr1,ptr2,&ptrmul);
        listShow(ptrmul);
        freeList(ptr1);freeList(ptr2);freeList(ptradd);freeList(ptrsub);freeList(ptrmul);
    }
    return 0;
}
void freeList(node* p)
{
   node* tmp;

   while (p != NULL)
    {
       tmp = p;
       p = p->next;
       free(tmp);
    }
}
node* getnode(void)
{
    node* p=(node*)malloc(sizeof(node));
    return p;
}

void freenode(node* p)
{
    free(p);
}

void listadd(node **p,int d,int c)
{
    if(*p==NULL){
        node* ptr=getnode();
        ptr-> degree = d;
        ptr-> coeff = c;
        ptr-> next = NULL;
        *p = ptr;
    }else{
        node* ptr=getnode();
        ptr-> degree = d;
        ptr-> coeff = c;
        ptr-> next = NULL;
        (*p) -> next = ptr;
        *p = ptr;
    }
}

int listEmpty(node* p)
{
    if(p==NULL)
    {
        return 1;
    }else
    {
        return 0;
    }
}

void listShow(node* p)
{
    node* ptrtemp=p;
    if(p==NULL)printf("0");
    while(ptrtemp!= NULL) 
    { 
        if(ptrtemp->degree ==0){
            printf("%d", ptrtemp->coeff);
        }else if(ptrtemp->degree==1){
            if(ptrtemp->coeff==1||ptrtemp->coeff==-1){
                if(ptrtemp->coeff==-1)printf("-");
                printf("x");  
            }else{
                printf("%dx", ptrtemp->coeff);  
            }
            
        }else{
            if(ptrtemp->coeff==1 ||ptrtemp->coeff==-1){
                if(ptrtemp->coeff==-1)printf("-");
                printf("x^%d",  ptrtemp->degree);
            }else{
                printf("%dx^%d", ptrtemp->coeff, ptrtemp->degree);
            }
             
        }
            ptrtemp = ptrtemp->next;  
        if(ptrtemp != NULL && ptrtemp->coeff>=0) 
            printf("+"); 
    }
    printf("\n");
}

int COMPARE(int a,int b)
{
    if(a<b)
    {
        return -1;
    }else if(a==b)
    {
        return 0;
    }else
    {
        return 1;
    }
} 
void getCoef(char *input,node** ptr)
{
    
    int i=0, coun=1;
    node* rear = *ptr;
    if(input[i]=='0' && input[i+1]=='\0'){
        return;
    }
    while(input[i]!='\0')
    {
        int j = i, c = 0, d = 0, sign=0;
        if(input[j]=='-' ){
                sign=1;
                j++;
        }else if(input[j]=='+'&& j!=0){
                j++;
        }
        while(input[j]!='x' && input[j]!='\0') //coeff(string->int)
        {
            c*=10;
            c+=input[j]-'0';
            j++;
        }
        if((input[j-1]=='+' ||input[j-1]=='-' || j==0)&& input[j]=='x'){
            c=1;
        }
        if(input[j+1]=='\0' && input[j]!='x'){//下一個為空 && 現在為X
            d=0;j++;
        }else if((input[j+1]=='+' ||input[j+1]=='-' || input[j+1]=='\0')&& input[j]=='x'){
            d=1;j++;
        }else if(input[j]!='\0'){
            j+=2;
            while(input[j]!='\0' && input[j]!='+' && input[j]!='-') //Degree(string->int)
            {
                d*=10;
                d+=input[j]-'0';
                j++;
            }
        }
        if(sign==1)c*=-1;
        listadd(&rear,d,c);
        if(coun==1) // 第一次要幫換掉位於 main funtion 的指標
        {
            *ptr = rear;
            coun=0;
        }
        i=j;
    }
}

void polyAdd(node* p1,node* p2,node** ptr)
{
    node* rear = *ptr;
    int coun = 1;
    int sum;
    while(p1!=NULL && p2!=NULL)
    {
        switch(COMPARE(p1->degree,p2->degree))
        {
            case -1:
                listadd(&rear,p2->degree,p2->coeff);
                p2 = p2->next;
                break;
            case 0:
                sum = p1->coeff + p2->coeff ;
                if(sum != 0)listadd(&rear,p1->degree,sum);
                p2 = p2->next;
                p1 = p1->next;
                break;
            case 1:
                listadd(&rear,p1->degree,p1->coeff);
                p1 = p1->next;
        }
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    for(;p1;p1=p1->next){
        listadd(&rear,p1->degree,p1->coeff);
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    for(;p2;p2=p2->next){
        listadd(&rear,p2->degree,p2->coeff);
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    if(coun==1 && rear!=NULL){
        *ptr = rear;
        coun = 0;
    }

}
void polySub(node* p1,node* p2,node** ptr)
{
    node* rear = *ptr;
    int coun = 1;
    int sum;
    while(p1 && p2)
    {
        switch(COMPARE(p1->degree,p2->degree))
        {
            case -1:
                listadd(&rear,p2->degree,(p2->coeff)*(-1));
                p2 = p2->next;
                break;
            case 0:
                sum = p1->coeff - p2->coeff ;
                if(sum != 0)
                {
                    listadd(&rear,p1->degree,sum);
                }
                p2 = p2->next;
                p1 = p1->next;
                break;
            case 1:
                listadd(&rear,p1->degree,p1->coeff);
                p1 = p1->next;
        }
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    for(;p1;p1=p1->next){
        listadd(&rear,p1->degree,p1->coeff);
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    for(;p2;p2=p2->next){
        listadd(&rear,p2->degree,(p2->coeff)*-1);
        if(coun==1 && rear!=NULL){
            *ptr = rear;
            coun = 0;
        }
    }
    if(coun==1 && rear!=NULL){
        *ptr = rear;
        coun = 0;
    }
}

void polyMul(node* p1,node* p2,node** ptr){
    for(;p1;p1=p1->next){
        node *tempp2=p2;
        node *temp1=NULL,*temp2=NULL;
        temp1=*ptr;
        node *rear = temp2;   
        int coun = 1;
        for(;tempp2;tempp2=tempp2->next){
            int d=p1->degree+tempp2->degree;
            int c=p1->coeff*tempp2->coeff;
            listadd(&rear,d,c);
            if(coun ==1){
                coun = 0;
                temp2 = rear;
            } 
        }
        node *temp=NULL;
        polyAdd(temp1,temp2,&temp);
        *ptr = temp;
    }
}
