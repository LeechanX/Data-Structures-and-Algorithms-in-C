#include <stdio.h>
#define N 8

int count;

void display_outcome(char *answer){
	int i;
	for(i=0;i<N;i++)
		printf("%c",answer[i]);
	printf("\n");
	count++;
}

int condition(char *string,char *answer,int step,int select){
	int i;
	int hash[26]={};
	int sp=0;
	for(i=0;i<N;i++)
		hash[string[i]-'a']++;
	for(i=0;i<step;i++)
		hash[answer[i]-'a']--;
	return hash[select];
}

void backtrack(char *string){
	char answer[N];
	int record[N];
	int step=0;
	record[step]=-1;
	while(step>=0){
		record[step]++;
		while(record[step]<26 && !condition(string,answer,step,record[step]))
			record[step]++;
		if(record[step]>=26)
			step--;
		else if(step==N-1){
			answer[step]=record[step]+'a';
			display_outcome(answer);
		}else{
			answer[step]=record[step]+'a';
			step++;
			record[step]=-1;
		}
	}
}

int main(int argc, char const *argv[])
{
	char *string="leechanx";
	backtrack(string);
	printf("%d\n",count);
	return 0;
}