#include <stdio.h>
#include <limits.h>

void method1(){
	int a=1;
	char *p=&a;
	if(*p)
		printf("小端\n");
	else
		printf("大端\n");
}

union Test{
	short a;
	char b;
};

void method2(){
	union Test test;
	test.a=1;
	if(test.b)
		printf("小端\n");
	else
		printf("大端\n");
}

void method3(){
	unsigned short limit=(USHRT_MAX+1)/2;
	unsigned short a=0;
	char name[1];
	printf("输入2字节字符串！\n");
	gets(name);
	if(a>=limit)
		printf("大端\n");
	else
		printf("小端\n");
}

main(){
	method1();
	method2();
	method3();
}
