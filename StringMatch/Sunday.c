#include <stdio.h>
#include <string.h>

int match(char *text,int texthead,char *pattern){
	int i=0;
	int retval=1;
	while(*(pattern+i) && *(text+texthead+i)==*(pattern+i))
		i++;
	if(*(pattern+i))
		retval=0;
	return retval;
}

int if_in_pattern(char *pattern,int psize,char ch){
	int i=psize-1;
	while(i>=0 && *(pattern+i)!=ch)
		i--;
	return i;
}

void sundaymatch(char *text,char *pattern,int tsize,int psize){
	int i=0;
	int step;
	char next;
	while(i<tsize-psize+1){
		if(match(text,i,pattern))
			printf("%d\n",i );
		if(i+psize<tsize){
			next=text[i+psize];
			step=if_in_pattern(pattern,psize,next);
			if(step>=0){
				i+=psize-step;
			}else{
				i=i+psize+1;
			}
		}else{
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	char *pattern="ababababca";
	char *text="bacabaabababaababababcabcaababababcabbababababababababcabab";
	int psize=strlen(pattern),tsize=strlen(text);
	sundaymatch(text,pattern,tsize,psize);
	return 0;
}