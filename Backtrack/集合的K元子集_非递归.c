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
	printf("(%d)\n",count);
}

int condition(int *answer,int target,int step,int select){
	int i;
	int count=0;
	for(i=0;i<step;i++)
		if(answer[i])
			count++;
	if(select)
		count++;
	return count;
}

int getsizeok(int *answer,int target){
	int count=0;
	for(int i=0;i<N;i++)
		if(answer[i])
			count++;
	return count==target;
}

void backtrack(int *set,int target){
	int answer[N];
	int record[N];
	int step=0;
	record[step]=-1;
	while(step>=0){
		record[step]++;
		while(record[step]<2 && condition(answer,target,step,record[step])>target)
			record[step]++;
		if(record[step]>=2)
			step--;
		else if(step==N-1){
			answer[step]=record[step];
			if(getsizeok(answer,target))
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
	int set[5]={93,12,43,9,87};
	backtrack(set,3);
	printf("subset size=%d\n", num);
	return 0;
}