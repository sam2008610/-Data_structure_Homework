#include<stdlib.h>
#include<stdio.h>
#define MAXN 100



typedef struct NODE{
    struct NODE *leftchild;
    struct NODE *rightchild;
    struct TNODE *parent;
    int inf;
}node;

typedef struct NODE *nodeptr;
nodeptr maketree(int);
nodeptr getnode();
void addtree(nodeptr,int);

void change(char[],int[],nodeptr);
void printPreorder(nodeptr);
void printInorder(nodeptr);
void printPostorder(nodeptr);

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        char input[MAXN];
        int number[MAXN];
        int digit = 0;
        nodeptr tree=NULL;
        scanf("%s",input);
        change(input,number,tree);
        printf("Preorder:");
        printPreorder(tree);
        printf("\n");
        printf("Inorder:");
        printInorder(tree);
        printf("\n");
        printf("Postorder:");
        printPostorder(tree);
        printf("\n");
    }
}

nodeptr maketree(int x){
    nodeptr p;
    p=getnode();
    p->inf=x;
    p->leftchild=NULL;
    p->rightchild=NULL;
    return p;
}

nodeptr getnode(){
    nodeptr p=(nodeptr)malloc(sizeof(node));
    return p;
}

void change(char *input,int *number,nodeptr tree){
    int i=0;
    while(input!='\0'){
        int sign=0, c=0;
        if(input[i]=='-'){
            sign=1;
            i++;
        }
        while(i!=',' && i!='\0'){
            c*=10;
            c+=(input[i]-'0');
            i++;
        }
        if(sign==1)
            c*=-1;
        addtree(tree,c);
    }
}
void addtree(nodeptr p , int x){
    if(p==NULL){
        
    }
}
void printPreorder(nodeptr p){
    if(p!=NULL){
        printf(" %d",p->inf);
        printPreorder(p->leftchild);
        printPreorder(p->rightchild);
    }
}
void printInorder(nodeptr p){
    if(p!=NULL){
        printInorder(p->leftchild);
        printf(" %d",p->inf);
        printInorder(p->rightchild);
    }   
}
void printPostorder(nodeptr p){
    if(p!=NULL){
        printPostorder(p->leftchild);
        printPostorder(p->rightchild);
        printf(" %d",p->inf);
    }
}