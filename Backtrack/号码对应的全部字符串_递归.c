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

void backtrack(int *number,int *answer,int step){
    if(step==N){
        display_outcome(number,answer);
    }else{
        int i;
        for(i=0;i<size[number[step]];i++){
            answer[step]=i;
            backtrack(number,answer,step+1);
        }
    }
}

int main(int argc, char const *argv[])
{
    int number[10]={4,8,6,9,4,6,8,6,6,4};
    int answer[10];
    backtrack(number,answer,0);
    return 0;
}