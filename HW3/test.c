#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define MAX_TREE_HT 100

typedef struct tagNode
{
    char character;
    unsigned frequency;
    struct tagNode *left, *right;
}HNode;

typedef struct tagHeap
{
    unsigned size;
    unsigned space;
    HNode **array;
}HHeap;

HNode* newNode(char character, unsigned frequency)
{
    HNode* temp = (HNode*)malloc(sizeof(HNode));
    temp->left = NULL;
    temp->right = NULL;
    temp->character = character;
    temp->frequency = frequency;
    return temp;
}

HHeap* createHHeap(unsigned space)
{
    HHeap* HHeapX = (HHeap*)malloc(sizeof(HHeap));
    HHeapX->size = 0;
    HHeapX->space = space;
    HHeapX->array = (HNode**)malloc(HHeapX->space * sizeof(HNode*));
    return HHeapX;
}

void swapHNode(HNode** a,HNode** b)
{
    HNode* t = *a;
    *a = *b;
    *b = t;
}

void HHeapify(HHeap* HHeapX, int idx)
{
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if ((left < HHeapX->size) && (HHeapX->array[left]->frequency < HHeapX->array[smallest]->frequency) )
    {
        smallest = left;
    }

    if ((right < HHeapX->size)&& (HHeapX->array[right]->frequency < HHeapX->array[smallest]->frequency))
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swapHNode(&HHeapX->array[smallest], &HHeapX->array[idx]);
        HHeapify(HHeapX, smallest);
    }
}

int isSizeOne(HHeap* HHeapX)
{
    return (HHeapX->size == 1);
}

HNode* extractMin(HHeap* HHeapX)
{
    HNode* temp = HHeapX->array[0];
    HHeapX->array[0] = HHeapX->array[HHeapX->size - 1];
    --HHeapX->size;
    HHeapify(HHeapX,0);
    return temp;
}

void insertHHeap(HHeap* HHeapX, HNode* HNodeX)
{
    //int i = HHeapX->size - 1;
    int i = HHeapX->size; //不减1
    ++HHeapX->size;
    while ((i > 1) && HNodeX->frequency < HHeapX->array[(i-1)/2]->frequency)
    {
        HHeapX->array[i] = HHeapX->array[(i-1)/2];
        i = (i-1)/2;
    }
    HHeapX->array[i] = HNodeX;
}

void buildHHeap(HHeap* HHeapX)
{
    int n = HHeapX->size - 1;
    for (int i = (n-1)/2; i >= 0 ; --i)
    {
        HHeapify(HHeapX, i);
    }
}

void printArr(int arr[],int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

int isLeaf(HNode* root)
{
    return !(root->left) && !(root->right) ;
}

HHeap* createAndBuildHHeap(char character[], int frequency[], int size)
{
    int i;
    HHeap* HHeapX = createHHeap(size);
    for (i = 0; i < size; ++i)
        HHeapX->array[i] = newNode(character[i], frequency[i]);
    HHeapX->size = size;
    buildHHeap(HHeapX);
    return HHeapX;
}

HNode* buildHuffmanTree(char character[], int frequency[], int size)
{
    HNode *l, *r, *top;
    HHeap* HHeap = createAndBuildHHeap(character, frequency, size);

    while (!isSizeOne(HHeap))
    {
        l = extractMin(HHeap);
        r = extractMin(HHeap);
        top = newNode('$', l->frequency + r->frequency);
        top->left = l;
        top->right = r;
        insertHHeap(HHeap, top);
    }
    return extractMin(HHeap);
}

void printCodes(HNode* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root))
    {
        printf("%c: ", root->character);
        printArr(arr, top);
    }
}

void HuffmanCoding(char character[], int frequency[], int size)
{
    HNode* root = buildHuffmanTree(character, frequency, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

int countStrFreq(const char *s, char character[], int frequency[])
{
    // 用表计算字符出现的频率
    int freq[128] = {0};
    while (*s)
    {
        freq[(int)*s++]++;
        //printf("%c",*s);
    }

    int c = 0;
    for (int i = 0; i < 128; i++)
    {
        if (freq[i] != 0)
        {
            character[c] = i;
            frequency[c] = freq[i];
            c++;
        }
    }
    return c;
}

void main()
{
    // 输入的字符串
    const char *str = "this is an example for huffman encoding";

    // ASCII码共包含128个字符，因此初始化大小设为128
    char cha[128];
    int freq[128]={0};

    // 计算字符串中各字符出现的频率
    int val;
    val = countStrFreq(str,cha,freq);

    // 进行Huffman编码
    HuffmanCoding(cha, freq, val);

    system("pause");
}

