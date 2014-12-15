#include <stdio.h>
#define SIZE 5

void print_answer(int *answer,int size){
	static int count;
	int i;
	for(i=0;i<size;i++)
		printf("%d ",answer[i]);
	printf("\n");
	count++;
}

void create_candidate(int *answer,int k,int *candidate,int *candidate_size){
	int sp=0;
	int hash[SIZE]={};
	int i;
	for(i=0;i<k;i++)
		hash[answer[i]-1]=1;
	for(i=0;i<SIZE;i++)
		if(!hash[i])
			candidate[sp++]=i+1;
	*candidate_size=sp;
}

void backtrack(int *set,int size,int *answer,int k){
	if(k==size)
		print_answer(answer,size);
	else{
		int candidate[SIZE];
		int candidate_size;
		create_candidate(answer,k,candidate,&candidate_size);
		int i;
		for(i=0;i<candidate_size;i++){
			answer[k]=candidate[i];
			backtrack(set,size,answer,k+1);
		}
	}
}

int main(int argc, char const *argv[])
{
	int set[]={1,2,3,4,5};
	int size=sizeof(set)/sizeof(int);
	int answer[SIZE];
	backtrack(set,size,answer,0);
	return 0;
}