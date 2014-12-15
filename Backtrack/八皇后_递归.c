#include <stdio.h>
#define SIZE 8

int count;

void display_outcome(int *answer){
	int i;
	for(i=0;i<SIZE;i++)
		printf("%d ",answer[i]);
	printf("\n");
	count++;
}

int inDiagonal(int x1,int y1,int x2,int y2){
	if(y1-y2==x1-x2 || y1-y2==x2-x1)
		return 1;
	return 0;
}

int condition(int *answer,int step,int select){
	int i;
	for(i=0;i<step;i++)
		if(answer[i]==select || inDiagonal(i,answer[i],step,select))
			return 0;
	return 1;
}

void create_candidate(int *answer,int step,int *candidate,int *candidate_size){
	int i,sp=0;
	for(i=0;i<SIZE;i++){
		if(condition(answer,step,i))
			candidate[sp++]=i;
	}
	*candidate_size=sp;
}

void backtrack(int *answer,int step){
	if(step==SIZE){
		display_outcome(answer);
	}else{
		int candidate[SIZE];
		int candidate_size;
		create_candidate(answer,step,candidate,&candidate_size);
		int i;
		for(i=0;i<candidate_size;i++){
			answer[step]=candidate[i];
			backtrack(answer,step+1);
		}
	}
}

int main(int argc, char const *argv[])
{
	int answer[SIZE];
	backtrack(answer,0);
	printf("count=%d\n", count);
	return 0;
}