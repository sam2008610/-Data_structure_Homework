#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 250
#define letterMAX 30

//node information
typedef struct HNODE{
    int weight; // frequency
    int lens; // how long
    int ch; //letter's ascii code
    char *code; // huffman code
}hnode;
hnode* gethnode();
void inputcode(hnode*);
//linked list's binary tree
typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    hnode *huffman;
}node;
typedef struct NODE *nodeptr;
nodeptr maketree(hnode*);
nodeptr getnode();

void count(int*,char);
void sortint(int*,int);
node* makehuffmantree(int*,hnode*);
void setletterhnode(hnode*,int);
void runnin(nodeptr);

int main(){
    int n; 
    int Letter[52];
    int letterCount=0;
    hnode Letterhnode[52];
    scanf("%d",&n);
    // initialize
    setletterhnode(Letterhnode,52);
    memset(Letter,0,sizeof(Letter));
    // read
    int j;
    for(j=0;j<n+1;j++){
        char temp;
        while(scanf("%c",&temp)!=EOF){
            if(temp=='\n'){
                break;
            }
            count(Letter,temp);
        }
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

void count(int *Letter,char input){
    if(input>='a' && input<='z'){
        Letter[input-'a'+26]+=1;
    }else if(input>='A' && input<='Z'){
        Letter[input-'a']+=1;
    }
}

node* makehuffmantree(int *c,hnode *huff){
    int queuelen=100;
    node h[queuelen];//tired to write a structure
    int front=0,rear=0;// queue front and rear
    int i=0;
    //lord the times into hnode which
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
        //insert new node to the queue
        int flag=0;
        node temp;
        int tempfront=front;
        while(((tempfront+2)%100)!=rear){
            if(flag==0){
                if(h[tempfront].huffman->weight <=newnode.huffman->weight && h[(tempfront+1)%100].huffman->weight>newnode.huffman->weight){
                    if(h[tempfront].huffman->lens<=newnode.huffman->lens && h[(tempfront+1)%100].huffman->lens>newnode.huffman->lens){
                        flag=1;
                        temp = newnode;
                    }
                }
            }else{
                h[tempfront]=temp;
                temp=h[(tempfront+1)%100];
            }
            tempfront=(tempfront+1)%100;
        }
        if(flag==0){
            h[rear]=temp;
        }else{
            h[rear]=newnode;
        }
    }
    nodeptr root=&h[front]; // return the root
    return root;
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

void setletterhnode(hnode* n,int leng){
    int i;
    for(int i=0;i<leng;i++){
        n[i].lens=0;
        n[i].weight=0;
        n[i].code=(char*)malloc(sizeof(char)*50);
        memset(n[i].code,'\0',sizeof(char)*50);
    }
}

void runnin(nodeptr p,char* parentcode,int codelong,char now){

}
