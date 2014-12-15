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

void backtrace(int *set,int size){
    int answer[size],record[size];
    #define N 2
    int step=0;
    record[step]=-1;
    int summary;
    while(step>=0){
        summary=sum(answer,step,set);
        record[step]++;
        if(record[step])
            summary+=set[step];
        if(record[step]>=N || summary>9)
            step--;
        else if(summary==9){
            answer[step]=record[step];
            displayoutcome(answer,set,step+1);
        }
        else if(step!=size-1){
            answer[step]=record[step];
            step++;
            record[step]=-1;
        }
    }
}

int main(){
    int set[]={7,5,1,2,8,4,3,10};
    int size=ARRAYSIZE(set);
    backtrace(set,size);
}
