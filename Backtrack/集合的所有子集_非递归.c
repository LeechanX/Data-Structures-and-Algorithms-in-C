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

void subset(int *set){
	int answer[N];
	int record[N];
	int step=0;
	record[step]=-1;
	while(step>=0){
		record[step]++;
		if(record[step]>=2)
			step--;
		else if(step==N-1){
			answer[step]=record[step];
			display_outcome(answer,set);
		}else{
			answer[step]=record[step];
			step++;
			record[step]=-1;
		}
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int set[5]={93,12,43,9,87};
	subset(set);
	printf("subset size=%d\n", num);
	return 0;
}