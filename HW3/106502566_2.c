#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_heap 100
#define max_code_size 100

typedef struct NODE{
    int weight;
    char character;
    struct NODE* left,*right;
    int *code;
    int codesize;
}node;

typedef struct HEAPNODE{
    int size ;
    int space;
    node **array;
}heapnode;

node* newNode(char c, int w){
    node* newNode=(node*)malloc(sizeof(node));
    newNode->weight=w;
    newNode->character=c;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->code=(int*)malloc(max_code_size*sizeof(int));
    newNode->codesize=0;
    return newNode;
}

heapnode* newHeap(int s){
    heapnode *heap =(heapnode*)malloc(sizeof(heap));
    heap->space=s;
    heap->array=(node**)malloc(heap->space* sizeof(node*));
    heap->size=0;
    return heap;
}

void swapnode(node** a,node** b){
    node* temp=*a;
    *a=*b;
    *b=temp;
}

void heapSort(heapnode* heap,int now){
    int small=now;
    int l=2*now+1;
    int r=2*now+2;
    if ((l < heap->size) && (heap->array[l]->weight < heap->array[small]->weight) )
    {
        small = l;
    }

    if ((r < heap->size)&& (heap->array[r]->weight < heap->array[small]->weight))
    {
        small = r;
    }

    if (small != now)
    {
        swapnode(&heap->array[small], &heap->array[now]);
        heapSort(heap, small);
    }
}
void heapSortByCodeLength(heapnode* heap,int now){
    int small=now;
    int l=2*now+1;
    int r=2*now+2;
    if ((l < heap->size) && (heap->array[l]->codesize < heap->array[small]->codesize ))
    {
        if(heap->array[l]->character < heap->array[small]->character )
            small = l;
    }

    if ((r < heap->size)&& (heap->array[r]->codesize  < heap->array[small]->codesize ))
    {
        if(heap->array[r]->character < heap->array[small]->character )
            small = r;
    }

    if (small != now)
    {
        swapnode(&heap->array[small], &heap->array[now]);
        heapSort(heap, small);
    }
}
void insertHeap(heapnode* heap,node* newnode){
    ++heap->size; //???
    int i=heap->size-1;
    while((i>1)&& newnode->weight<heap->array[(i-1)/2]->weight){
        heap->array[i] = heap->array[(i-1)/2];
        i = (i-1)/2;
    }
    heap->array[i]=newnode;
}

void buildHeap(heapnode* heap){
    int s = heap->size - 1;
    int i;
    for (i = (s-1)/2; i >= 0 ; --i)
    {
        heapSort(heap, i);
    }
}
void printArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){
        printf("%d",arr[i]);
    }
}
node* pop(heapnode* heap){
    node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    heapSort(heap,0);
    return temp;
}
heapnode* createAndBuildHHeap(char character[], int fre[], int size)
{
    int i;
    heapnode* heap = newHeap(size);
    for (i = 0; i < size; ++i)
        heap->array[i] = newNode(character[i], fre[i]);
    heap->size = size;
    buildHeap(heap);
    return heap;
}
node* buildHuffmanTree(char character[], int fre[], int size)
{
    node *l, *r, *top;
    heapnode* heap = createAndBuildHHeap(character, fre, size);

    while (heap->size!=1)
    {
        l = pop(heap);
        r = pop(heap);
        top = newNode('$', l->weight + r->weight);
        top->left = l;
        top->right = r;
        top->codesize=0;
        insertHeap(heap, top);
    }
    return pop(heap);
}
int count(int Letter[],char input){
    int coun=0;

    return coun;
}
int printCodes(node* root, int arr[], int top,heapnode* heap)
{
    int coun=0;
    if (root->left)
    {
        arr[top] = 0;
        coun+=printCodes(root->left, arr, top + 1,heap);
    }

    if (root->right)
    {
        arr[top] = 1;
        coun+=printCodes(root->right, arr, top + 1,heap);
    }

    if (root->left==NULL && root->right==NULL)
    {
        root->codesize=top;
        int i;
        for(i=0;i<top;i++){
            root->code[i]=arr[i];
        }
        insertHeap(heap,root);
        coun+=(root->codesize)*(root->weight);
        return coun;
    }
}
int makeHuffman(char character[],int Letter[],int size){
    node* root = buildHuffmanTree(character, Letter, size);
    int arr[max_heap], top = 0;
    heapnode* heap=newHeap(max_heap);
    int coun=0;
    coun+=printCodes(root, arr, top,heap);
    int s = heap->size - 1;
    int i;
    for (i = (s-1)/2; i >= 0 ; --i)
        heapSortByCodeLength(heap,i);
    for(i=0;i<heap->size;i++){
        printf("%c : ",heap->array[i]->character);
        printArray((heap->array[i]->code),heap->array[i]->codesize);
        printf("\n");
    }
    return coun;
}
int readAndCount(int n,int Letter[],char cha[],int* size){
    int letterCount=0;
    int j;
    int l[52]={0};
    char ch[52];
    for(j=0;j<n+1;j++){
        char temp;
        while(scanf("%c",&temp)!=EOF){
            if(temp=='\n'){
                break;
            }
            if(temp>='a' && temp<='z'){
                l[temp-'a'+26]+=1;
                ch[temp-'a'+26]=temp;
                letterCount++;
            }else if(temp>='A' && temp<='Z'){
                l[temp-'A']+=1;
                ch[temp-'A']=temp;
                letterCount++;
            }
        }
    }
    int i,c=0;
    for (i = 0; i < 52; i++)
    {
        if (l[i] != 0)
        {
            cha[c] = ch[i];
            Letter[c] = l[i];
            c++;
        }
    }
    *size=c;
    return letterCount;
}
int main(){
    int n,size;
    int Letter[52]={0};
    char cha[52];    
    int letterCount=0;
    scanf("%d",&n);
    memset(Letter,0,sizeof(Letter));    
    letterCount=readAndCount(n,Letter,cha,&size);
    int coun=makeHuffman(cha,Letter,size);
    printf("%d\n",coun);
    double a=coun,b=letterCount*4;
    printf("Compression ratio: %.2lf",a/b);
    return 0;
}