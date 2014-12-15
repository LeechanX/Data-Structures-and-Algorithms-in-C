#include <stdio.h>
#define PEOPLE 6
#define YIYUAN 3
#define WUMAO 3

void display_outcome(int *answer){
	int i;
	for(i=0;i<PEOPLE;i++)
		printf("%d",answer[i]);
	printf("\n");
}

int condition(int *answer,int step,int select){
	int fivemao=0,oneyuan=0;
	int i;
	for(i=0;i<step;i++){
		if(answer[i])
			oneyuan++;
		else
			fivemao++;
	}
	if(select)
		oneyuan++;
	else
		fivemao++;
	return (oneyuan<=fivemao) && (oneyuan<=YIYUAN && fivemao<=WUMAO);
}

void backtrack(){
	int record[PEOPLE];
	int step=0;
	int answer[PEOPLE];
	record[step]=-1;
	while(step>=0){
		record[step]++;
		while(record[step]<2 && !condition(answer,step,record[step]))
			record[step]++;
		if(record[step]>=2)
			step--;
		else if(step==PEOPLE-1){
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
	return 0;
}