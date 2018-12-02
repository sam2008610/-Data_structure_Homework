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
hnode* gethnode();
void inputcode(hnode*);
//linked list 的 binary tree
typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    hnode *huffman;
}node;
typedef struct NODE *nodeptr;
nodeptr maketree(hnode*);
nodeptr getnode();

int count(int*,char*);
void sortint(int*,int);
void makehuffmantree(int*,hnode*);
void insertqueue(node*,node,int,int);
void setletterhnode(hnode*,int);

int main(){
    int n; 
    int Letter[52];
    int letterCount=0;
    hnode Letterhnode[52];
    setletterhnode(Letterhnode,52);
    memset(Letter,0,sizeof(Letter));
    scanf("%d",&n);
    while(n--){
        char input[MAXN];
        scanf("%[^\n]",input);
        letterCount+=count(Letter,input);
        
    }
    sortint(Letter,52);
    makehuffmantree(Letter,Letterhnode);
    printf("Compression ratio: ");
}

nodeptr getnode(){
    nodeptr p=(nodeptr)malloc(sizeof(node));
    return p;
}

hnode* gethnode(){
    hnode* p=(hnode*)malloc(sizeof(hnode));
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
    int queuelen=100;
    node h[queuelen];//tired to write a structure
    int front=0,rear=0;
    int i=0;
    for(i=0 ; i<52 ; i++){
        if(c[i]==0){
            continue;
        }else{
            h[front].huffman=huff+i;
            huff[i].lens=1;
            huff[i].weight=c[i];
            huff[i].ch=i; 
            rear=(rear+1)%queuelen;
        }
    }
    while((front+1)%52!=rear){
        node temp1=h[front];
        node temp2=h[front+1];
        node newnode;
        newnode.leftchild=&temp1;
        newnode.rightchild=&temp2;
        (newnode.huffman)->weight=(temp1.huffman)->weight+(temp2.huffman)->weight;
        (newnode.huffman)->lens=(temp1.huffman)->lens+(temp2.huffman)->lens;
        front+=2;
        insertqueue(h,newnode,front,rear);
    }
    
}

void sortint(int *num,int length){
    int i;
    for(i=0; i<length ;i++){
        int j;
        for(j=0; j<length-1 ;j++){
            if(num[j+1]<num[j]){
                int temp=num[j+1];
                num[j+1]=num[j];
                num[j]=temp;
            }
        }
    }
}

void insertqueue(node *q,node newnode,int front,int rear){
    int flag=0;
    node temp;
    while(((front+2)%100)!=rear){
        if(flag==0){
            if(q[front].huffman->weight <=newnode.huffman->weight && q[(front+1)%100].huffman->weight>newnode.huffman->weight){
                if(q[front].huffman->lens<=newnode.huffman->lens && q[(front+1)%100].huffman->lens>newnode.huffman->lens){
                    flag=1;
                    temp = newnode;
                }
            }
        }else{
            q[front]=temp;
            temp=q[(front+1)%100];
        }
        front=(front+1)%100;
    }
    if(flag==0){
        q[rear]=temp;
    }else{
        q[rear]=newnode;
    }
} 

void setletterhnode(hnode* n,int leng){
    int i;
    for(int i=0;i<leng;i++){
        n[i].lens=0;
        n[i].weight=0;
    }
}