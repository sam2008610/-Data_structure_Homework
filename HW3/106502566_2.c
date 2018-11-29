#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 250
#define letterMAX 30

//節點資訊
typedef struct HNODE{
    int weight;
    int lens;
    int ch;
    char *code;
}hnode;
typedef struct hnode *hnodeptr;
hnodeptr gethnode();
void inputcode(hnodeptr);
//linked list 的 binary tree
typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    hnodeptr huffman;
}node;
typedef struct NODE *nodeptr;
nodeptr maketree(hnodeptr);
nodeptr getnode();

int count(int*,char*);
void sort(int*,int);
void makehuffmantree(int*,hnode*);

int main(){
    int n; 
    int Letter[52];
    int letterCount=0;
    memset(Letter,0,sizeof(Letter));
    while(n--){
        char input[MAXN];
        hnode Letterhnode[52];
        scanf("%s",input);   
        letterCount+=count(Letter,input);
        sort(Letter,52);
        makehuffmantree(Letter,Letterhnode);

    }
    
    printf("Compression ratio: ");
}
nodeptr maketree(hnodeptr input){
    nodeptr p;
    p=getnode();
    p->leftchild=NULL;
    p->rightchild=NULL;
    p->huffman=NULL;
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

void makehuffmantree(int *c,hnode *huff){
    node h[100];//tired to write a structure
    int front=0,rear=0;
    int i=0;
    for(i=0 ; i<52 ; i++){
        if(c[i]==0){
            continue;
        }else{

        }
    }
    while((front+1)%52==rear){

    }
}