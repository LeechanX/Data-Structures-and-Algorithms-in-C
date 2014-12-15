#include <stdio.h>
#define SIZE 5

void print_answer(int *answer){
	static int count;
	int i;
	for(i=0;i<SIZE;i++)
		printf("%d ",answer[i]);
	printf("\n");
	count++;
}

int condition(int *answer,int select,int step){
	int i;
	for(i=0;i<step;i++)
		if(answer[i]==select)
			return 0;
	return 1;
}

void backtrack(int *set){
	int step=0;
	int record[SIZE],answer[SIZE];
	record[step]=-1;
	while(step>=0){
		record[step]++;
		while(record[step]<SIZE && !condition(answer,record[step]+1,step))
			record[step]++;
		if(record[step]>SIZE-1){
			step--;
		}else if(step==SIZE-1){
			answer[step]=record[step]+1;
			print_answer(answer);
		}else{
			answer[step]=record[step]+1;
			step++;
			record[step]=-1;
		}
	}
}

int main(int argc, char const *argv[])
{
	int set[]={1,2,3,4,5};
	backtrack(set);
	return 0;
}