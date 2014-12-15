#include <stdio.h>

void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

int gcd(int a,int b){
	int mod;
	if(a<b)
		swap(&a,&b);
	while(mod=a%b){
		a=b;
		b=mod;
	}
	return b;
}

int main(int argc, char const *argv[])
{
	int a,b;
	int the_gcd,the_lcm;
	while(scanf("%d%d",&a,&b)){
		the_gcd=gcd(a,b);
		the_lcm=a*b/the_gcd;
		printf("最大公约数=%d\n",the_gcd);
		printf("最小公倍数=%d\n",the_lcm);
	}
	return 0;
}