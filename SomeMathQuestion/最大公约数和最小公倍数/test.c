#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	if(n=0)
		printf("n=0\n");
	if(n=1)
		printf("n=1\n");
	if(!(n=0))
		printf("!(n=0)\n");
	printf("%d\n",n=3 );
	return 0;
}