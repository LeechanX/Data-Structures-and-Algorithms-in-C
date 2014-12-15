#include <stdio.h>
#include <stdlib.h>
#define LIMIT 20

void countsort(int *data,int size){
	int counts[LIMIT]={},i;
	int datacopy[size];
	for(i=0;i<size;i++){
		counts[data[i]]++;
		datacopy[i]=data[i];
	}
	for(i=1;i<LIMIT;i++)
		counts[i]+=counts[i-1];
	for(i=size-1;i>=0;i--)
		data[--counts[datacopy[i]]]=datacopy[i];
}

void displayoutcome(int *data,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", *(data+i));
	printf("\n");
}

int main(){
	/*
	时间复杂度:O(n)
	空间复杂度:O()
	适用于属于一定范围内的数的排序。
	思路:。
	*/
	int data[]={5,4,3,19,3,9,16,15,0,
		0,9,12,9,10,10,4,19,15,12,16,
		0,0,1,1,3,4,14,3,6,12,1,3,14,
		4,15,4,4,7,11,13,2,1,15,13,1,
		12,9,17,13,16,};
	int size=sizeof(data)/sizeof(int);
	countsort(data,size);
	displayoutcome(data,size);
	return 0;
}
