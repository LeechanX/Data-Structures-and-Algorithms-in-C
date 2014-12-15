#include <stdio.h>
#include <string.h>
#define BOYSIZE 4
#define BOY 0
#define GIRLSIZE 4
#define GIRL 4
#define TRUE 1
#define FALSE 0

int match[BOYSIZE][GIRLSIZE]={
    {1,1,0,0},{0,1,1,0},{1,1,0,0},{0,0,1,0}
};

int findout(int *mygirl,int *myboy,int boy,int *used){
    int j;//
    for(j=0;j<GIRLSIZE;j++)
        if(match[boy][j] && !used[j]){
            used[j]=1;
            if(myboy[j]==-1 || findout(mygirl,myboy,myboy[j],used)){
                myboy[j]=boy;
                mygirl[boy]=j;
                return TRUE;
            }
        }
    return FALSE;
}

void display(int *mygirl){
    int i;
    for(i=0;i<BOYSIZE;i++)
        printf("%d=>%d\n",i,mygirl[i]);
}

int xyl(int *mygirl,int *myboy){
    int i,counter=0;
    int used[GIRLSIZE]={};
    for(i=0;i<BOYSIZE;i++){
        memset(used,0,sizeof(used));
        if(findout(mygirl,myboy,i,used))
            counter++;
    }
    display(mygirl);
    return counter;
}

int main(){
    int mygirl[BOYSIZE]={-1,-1,-1,-1};
    int myboy[GIRLSIZE]={-1,-1,-1,-1};
    int counter=xyl(mygirl,myboy);
    printf("counter=%d\n",counter);
}
