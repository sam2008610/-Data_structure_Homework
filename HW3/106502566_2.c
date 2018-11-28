#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 250
#define letterMAX 30

typedef struct HNODE{
    int weight;
    int lens;
    char c[letterMAX];
}hnode;
typedef struct hnode *hnodeptr;
hnodeptr gethnode();

typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    hnodeptr inf;
}node;
typedef struct NODE *nodeptr;


int count(int*,char*);
nodeptr maketree(hnodeptr);
nodeptr getnode();
void addtree(node**,int);

int main(){
    int n; 
    int Letter[52];
    int letterCount=0;
    memset(Letter,0,sizeof(Letter));
    while(n--){
        char input[MAXN];
        scanf("%s",input);   
        letterCount+=count(Letter,input);
    }
    printf("Compression ratio: ");
}
nodeptr maketree(hnodeptr input){
    nodeptr p;
    p=getnode();
    hnodeptr p2;
    p2=gethnode();
    //未完
    p->leftchild=NULL;
    p->rightchild=NULL;
    return p;
}

nodeptr getnode(){
    nodeptr p=(nodeptr)malloc(sizeof(node));
    return p;
}

hnodeptr gethnode(){
    hnodeptr p=(hnodeptr)malloc(sizeof(hnode));
    return p;
}
int count(int *Letter,char *input){
        int i=0,letterCount=0;
        while(input[i]!='\0'){
            if(input[i]>='a' && input[i]<='z'){
                Letter[input[i]-'a'+26]+=1;
                letterCount++;
            }else if(input[i]>='A' && input[i]<='Z'){
                Letter[input[i]-'a']+=1;
                letterCount++;
            }
            i++;
        }
    return letterCount;
}