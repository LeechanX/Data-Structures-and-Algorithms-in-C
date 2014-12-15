#include <stdio.h>
#define ARRAYSIZE(array) sizeof array/sizeof *array

void displayoutcome(int *answer,int *set,int step){
    int i;
    for(i=0;i<step;i++)
        if(*(answer+i))
            printf("%d ",*(set+i));
    printf("\n");
}

int sum(int *answer,int step,int *set){
    int i,sum=0;
    for(i=0;i<step;i++)
        if(*(answer+i))
            sum+=*(set+i);
    return sum;
}

void backtrace(int *answer,int step,int *set,int size){
    int summary=sum(answer,step,set);
    if(summary==9){
        displayoutcome(answer,set,step);
        return ;
    }
    if(step==size || summary>9)
        return ;
    int i;
    for(i=0;i<2;i++){
        answer[step]=i;
        backtrace(answer,step+1,set,size);
    }
}

int main(){
    int set[]={7,5,1,2,8,4,3,10};
    int size=ARRAYSIZE(set);
    int answer[size];
    backtrace(answer,0,set,size);
}
