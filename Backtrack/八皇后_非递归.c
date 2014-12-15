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

void backtrack(){
	int step=0;
	int record[SIZE];
	record[step]=-1;
	int answer[SIZE];
	while(step>=0){
		record[step]++;
		while(record[step]<SIZE && !condition(answer,step,record[step]))
			record[step]++;
		if(record[step]>SIZE-1)
			step--;
		else if(step==SIZE-1){
			answer[step]=record[step];
			display_outcome(answer);
		}else{
			answer[step]=record[step];
			step++;
			record[step]=-1;
		}
	}
}

int main(int argc, char const *argv[])
{
	backtrack();
	printf("count=%d\n", count);
	return 0;
}