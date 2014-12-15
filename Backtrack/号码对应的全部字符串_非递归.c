#include <stdio.h>
#define N 10

static char ch[10][4] =
{
    "",
    "",
    "ABC",
    "DEF",
    "GHI",
    "JKL",
    "MNO",
    "PQRS",
    "TUV",
    "WXYZ",
};
int size[10]={0,0,3,3,3,3,3,4,3,4};

void display_outcome(int *number,int *answer){
    int i;
    for(i=0;i<N;i++)
        printf("%c",ch[number[i]][answer[i]]);
    printf("\n");
}

void backtrack(int *number){
    int record[N];
    int answer[N];
    int step=0;
    record[step]=-1;
    while(step>=0){
        record[step]++;
        if(record[step]>=size[number[step]])
            step--;
        else if(step==N-1){
            answer[step]=record[step];
            display_outcome(number,answer);
        }else{
             answer[step]=record[step];
             step++;
             record[step]=-1;
        }
    }
}

int main(int argc, char const *argv[])
{
    int number[10]={4,8,6,9,4,6,8,6,6,4};
    backtrack(number);
    return 0;
}