#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 6
#define K 18

void displayoutcome(int *set,int *answer,int size){
	int i;
	for(i=0;i<size;i++)
		if(answer[i])
			printf("%d ",set[i] );
	printf("\n");
}

int sum(int *set,int *answer,int size){
	int summary=0,i;
	for(i=0;i<size;i++)
		if(answer[i])
			summary+=set[i];
	return summary;
}

void BFS_search(int *set,int *answer,int step){
	int summary=sum(set,answer,step);
	if(step==SIZE ){
		if(summary==K)
			displayoutcome(set,answer,step);
		return ;
	}
	int sel;
	for(sel=0;sel<2;sel++){
		answer[step]=sel;
		BFS_search(set,answer,step+1);
	}
}

void branchbound(int *set,int *answer,int step){
	int summary=sum(set,answer,step);
	if(summary>K){
		printf("Drop branch.\n");
		return ;
	}
	if(step==SIZE){
		if(summary==K)
			displayoutcome(set,answer,step);
		return ;
	}
	int sel;
	for(sel=0;sel<2;sel++){
		answer[step]=sel;
		branchbound(set,answer,step+1);
	}
}

int main(int argc, char const *argv[])
{
	int set[SIZE]={7,4,6,13,20,8};
	int answer[SIZE];
	printf("use DFS:\n");
	BFS_search(set,answer,0);
	printf("use Branch and Bound:\n");
	branchbound(set,answer,0);
	return 0;
}