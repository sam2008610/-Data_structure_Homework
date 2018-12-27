#include<stdio.h>
#include<stdlib.h>
#define Max_num 80000
void printArray(int num[],int size){
    int i;
    for(i=0; i<size ;i++){
        printf("%d ",num[i]);
    }
    printf("\n");
}
int read(int num[]){
    int i=0;
    int coun=0;
    char input[Max_num];
    scanf("%s",input);
    while(input[i]!='\0'){
        int sign=0, c=0;
        if(input[i]=='-'){
            sign=1;
            i++;
        }
        while(input[i]!=',' && input[i]!='\0'){
            c*=10;
            c+=(input[i]-'0');
            i++;
        }
        if(input[i]!='\0')
            i++;
        if(sign==1)
            c*=-1;
        num[coun]=c;
        coun++;
    }
    return coun;
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0; k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle= left+(right-left)/2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}
int main(){
    int cases;
    int num[Max_num];
    scanf("%d",&cases);
    while(cases--){
        int size=read(num);
        mergeSort(num,0,size-1);
        printArray(num,size);
    }
}
