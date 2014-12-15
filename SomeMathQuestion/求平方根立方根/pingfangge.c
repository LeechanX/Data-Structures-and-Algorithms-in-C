#include <stdio.h>

double myabs(double x){
	if(x>=0)
		return x;
	return x*(-1);
}

double squareroot(int n,double accuracy){
	double x=n;
	while(myabs(x*x-n)>accuracy)
		x=(x+n*1.0/x)/2;
	return x;
}

int main(int argc, char const *argv[])
{
	int d;
	double accuracy=0.00001;
	while(scanf("%d",&d)==1){
		printf("%d平方根=%f\n",d,squareroot(d,accuracy));
	}
	return 0;
}