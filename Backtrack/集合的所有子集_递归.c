#include <stdio.h>
#define N 5

int num;

void display_outcome(int *answer,int *set){
	int i;
	num++;
	int count=0;
	for(i=0;i<N;i++)
		if(answer[i]){
			printf("%d ",set[i]);
			count++;
		}
	printf("!(%d)\n",count);
}

void subset(int *set,int *answer,int step){
	if(step==N)
		display_outcome(answer,set);
	else{
		int i;
		for(i=0;i<2;i++){
			answer[step]=i;
			subset(set,answer,step+1);
		}
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int set[5]={93,12,43,9,87};
	int answer[5]={};
	subset(set,answer,0);
	printf("subset size=%d\n", num);
	return 0;
}