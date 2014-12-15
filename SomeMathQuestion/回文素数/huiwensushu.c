#include <stdio.h>

int isPalindrome(unsigned);
void create_flag(void);
int isPrim(int);

int main(int argc, char const *argv[])
{
	unsigned i;
	for(i=1;i<(unsigned)10000;i++)
		if(isPrim(i))
			if(isPalindrome(i))
				printf("%d\n",i );
	return 0;
}