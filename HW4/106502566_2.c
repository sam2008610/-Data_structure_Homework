#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_size 30
#define Max_char 150
#define Max_int 0x3f3f3f3f
// void printArray(int num[],int size){
//     int i,j;
//     for(i=0; i<size ;i++){
//        for(j=0 ;j<size ;j++){
//            printf("%d ",num[i*size+j]);
//        }
//     printf("\n");
//     }
    
// }
int read(int gra[]){
    int size;
    scanf("%d",&size);
    int i=size,j=0;
    while(i--){
        int k=0;
        char input[Max_char];
        scanf("%s",input);
        while(input[k]!='\0'){
            int sign=0, c=0;
            if(input[k]=='-'){
            sign=1;
            k++;
            }
            while(input[k]!=',' && input[k]!='\0'){
            c*=10;
            c+=(input[k]-'0');
            k++;
            }
            if(input[k]!='\0')
                k++;
            if(sign==1)
                c*=-1;
            gra[j+(size-i-1)*size]=c;
            j++;
        }
        j=0;
    }
    return size;
}
void primsalgo(int gra[],int spanning[],int size){
    int visited[Max_size],vistedcoun=0,parent[Max_size];
    memset(visited,0,Max_size);
    visited[0]=1;
    while((size-1)!=vistedcoun){
        int minedge=Max_int;
        int i,j,si,sj;
        for(i=0;i<size;i++){
            if(visited[i]==0)continue;
            for(j=0;j<size;j++){
                if(gra[i*size+j]!=0 && visited[j]==0 && gra[i*size+j]<minedge){
                    minedge=gra[i*size+j];
                    si=i;sj=j;
                }                                    
            }
        }
        vistedcoun++;
        gra[si*size+sj]=gra[sj*size+si]=0;
        spanning[si*size+sj]=minedge;
        visited[sj]=1;
        parent[sj]=si;
        printf("%c-%c %d\n",si+'A',sj+'A',minedge);        
    } 
}
int main(){
    int cases;
    scanf("%d",&cases);
    int i=cases;
    while(i--){
        int gra[Max_size*Max_size],spanning[Max_size*Max_size];
        memset(gra,0,Max_size*Max_size);
        memset(spanning,0,Max_size*Max_size);
        int size=read(gra);
        printf("Case %d:\n",cases-i);
        primsalgo(gra,spanning,size);
    }
    
}