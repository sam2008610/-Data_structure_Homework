#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_size 30
#define Max_char 150
#define Max_int 0x3f3f3f3f
int read(int gra[]){
    int size;
    scanf("%d",&size);
    int i=size,j=0;
    while(i--){
        char input[Max_char];
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
            gra[j+(i-size)*size]=c;
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
    while(size!=vistedcoun){
        int minedge=Max_int;
        int i,j,si,sj;
        for(i=0;i<size;i++){
            if(visited[i]==1)continue;
            for(j=0;j<size;j++){
                if(gra[i*size+j]!=0 && visited[j]==0 && gra[i*size+j]<minedge){
                    minedge=gra[i*size+j];
                    si=i;sj=j;
                }                                    
            }
        }
    } 
}
int main(){
    int cases;
    scanf("%d",&cases);
    while(cases--){
        int gra[Max_size*Max_size],spanning[Max_size*Max_size];
        memset(gra,0,Max_size*Max_size);
        memset(spanning,0,Max_size*Max_size);
        int size=read(gra);
        primsalgo(gra,spanning,size);
    }
    
}