#include<stdio.h>
#include<stdlib.h>

int main(){
    int Letter[52];
    int n;
    scanf("%d",&n);
    int j;
    for(j=0;j<n+1;j++){
        char temp;
        while(scanf("%c",&temp)!=EOF){
            if(temp=='\n'){
                break;
            }
            printf("%c\n",temp);
        }
    }
}