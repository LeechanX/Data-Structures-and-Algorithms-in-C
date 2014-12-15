#include <stdio.h>
#include <stdlib.h>
#define LIMIT 20

int getvalue(int number,int pos){
	while(pos>1){
		number=number/10;
		pos--;
	}
	number%=10;
	return number;
}

void countsort(int *data,int size,int pos){
	int counts[LIMIT]={},i;
	int *datacopy=malloc(sizeof(int)*size);
	for(i=0;i<size;i++){
		counts[getvalue(data[i],pos)]++;
		datacopy[i]=data[i];
	}
	for(i=1;i<LIMIT;i++)
		counts[i]+=counts[i-1];
	for(i=size-1;i>=0;i--){
		data[counts[getvalue(datacopy[i],pos)]-1]=datacopy[i];
		counts[getvalue(datacopy[i],pos)]--;
	}
}

void radix_sort(int *data,int size,int digitsize){
	int i;
	for(i=1;i<=digitsize;i++)
		countsort(data,size,i);
}

void displayoutcome(int *data,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", *(data+i));
	printf("\n");
}

int main(){
	/*
	*/
	int data[]={64,8,216,512,27,729,0,1,343,125,93};
	int size=sizeof(data)/sizeof(int);
	radix_sort(data,size,3);
	displayoutcome(data,size);
	return 0;
}