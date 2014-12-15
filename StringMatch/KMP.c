#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isprefix(char *string,char *teststring,int testsize){
	int retval=0;
	int i=0;
	while(i<testsize && *(string+i)==*(teststring+i))
		i++;
	if(i==testsize)
		retval=1;
	return retval;
}

int getlongestprefix(char *string,int size){
	int retval=0;
	int i;
	for(i=1;i<size;i++)
		if(isprefix(string,string+i,size-i)){
			retval=size-i;
			break;
		}
	return retval;
}

int *create_jumptable(char *pattern,int size){
	int *jumptable=malloc(sizeof(int)*size);
	int i;
	for(i=0;i<size;i++)
		jumptable[i]=getlongestprefix(pattern,i+1);
	return jumptable;
}

int match(char *text,int texthead,char *pattern){
	int matchsize=0;
	while(*(matchsize+pattern) && *(text+texthead+matchsize)==*(pattern+matchsize))
		matchsize++;
	return matchsize;
}

void KMPmatch(char *text,char *pattern,int tsize,int psize,int *jumptable){
	int i=0;
	int solution;
	while(i<tsize-psize+1){
		solution=match(text,i,pattern);
		if(solution){
			if(solution==psize)
				printf("%d\n", i);
			i+=solution-jumptable[solution-1];
		}else
			i++;
	}
}

int main(int argc, char const *argv[])
{
	char *pattern="ababababca";
	char *text="bacabaabababaababababcabcaababababcabbababababababababcabab";
	int psize=strlen(pattern),tsize=strlen(text);
	int *jumptable=create_jumptable(pattern,psize);
	KMPmatch(text,pattern,tsize,psize,jumptable);
	return 0;
}