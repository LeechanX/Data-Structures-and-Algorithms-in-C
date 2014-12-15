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

void backtrack(int *answer,int step){
	if(step==PEOPLE)
		display_outcome(answer);
	else
		for(int i=0;i<2;i++)
			if(condition(answer,step,i)){
				answer[step]=i;
				backtrack(answer,step+1);
			}
}

int main(int argc, char const *argv[])
{
	int answer[PEOPLE];
	backtrack(answer,0);
	return 0;
}