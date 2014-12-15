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

void backtrack(int *set,int *answer,int target,int step){
	if(step==N){
		if(getsizeok(answer,target))
			display_outcome(answer,set);
	}else{
		int i;
		for(i=0;i<2;i++){
			if(condition(answer,target,step,i)<=target){
				answer[step]=i;
				backtrack(set,answer,target,step+1);
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int set[N]={93,12,43,9,87};
	int answer[N];
	backtrack(set,answer,3,0);
	printf("subset size=%d\n", num);
	return 0;
}