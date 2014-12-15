#include <stdio.h>

int fib_recursive(int n){
	if(n<=1)
		return 1;
	else
		return fib_recursive(n-1)+fib_recursive(n-2);
}

int fib_nor(int n){
	if(n<=1)
		return 1;
	int prev,prev2;
	prev=prev2=1;
	int answer=0;
	for(int i=2;i<=n;i++){
		answer=prev+prev2;
		prev=prev2;
		prev2=answer;
	}
	return answer;
}

int main(int argc, char const *argv[])
{
	int n;
	while(scanf("%d",&n)){
		printf("%d\n",fib_recursive(n));
		printf("%d\n",fib_nor(n));
	}
	return 0;
}