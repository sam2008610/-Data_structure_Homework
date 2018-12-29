#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define Max_size 1050
#define Max_int 0x3f3f3f3f
typedef struct NODE{
    int x;
    int y;
}node;
void readandcaluate(int cases,int c){
    node city[Max_size];
    int size,threshold;
    scanf("%d %d",&size,&threshold);
    int i=size;
    while(i--){
        scanf("%d %d",&city[size-i-1].x,&city[size-i-1].y);
    }
    printf("Case %d: ",cases-c);
    int k,j;
    int visited[Max_size],visitedcount=0,state=0,roads=0,railroads=0;
    node remeb[Max_size];
    int rem=1;
    memset(visited,0,Max_size);
    visited[0]=1;
    while((size-1)!=visitedcount){
        int minedge=Max_int;
        int si=-1,sj=-1;
        for(i=0;i<size;i++){
            if(visited[i]==0)continue;
            for(j=0;j<size;j++){
                double distancex=0,distancey=0,distance;
                distancex=city[i].x-city[j].x;
                distancey=city[i].y-city[j].y;
                distance=round(sqrt(distancex*distancex+distancey*distancey));
                if((int)distance<minedge && visited[j]==0 ){
                    int find=0;
                    int h;
                    for(h=0;h<rem;h++){
                        if((remeb[h].x==i &&remeb[h].y==j)||(remeb[h].x==j &&remeb[h].y==i)){
                            find=1;
                        }
                    }
                    if(find==0){
                        minedge=(int)distance;
                        sj=j;
                        si=i;
                    }
                }                                  
            }
        }
        visitedcount++;
        remeb[rem].x=si;remeb[rem].y=sj;
        rem++;
        if(minedge>=threshold){
            state++;
            railroads+=minedge;
        }else{
            roads+=minedge;
        }
        visited[sj]=1;
    }
    printf("%d %d %d\n",state+1,roads,railroads);
}
int main(){
    int cases;
    scanf("%d",&cases);
    int i=cases;
    while(i){
        i--;
        readandcaluate(cases,i);
    }
}