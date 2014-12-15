#include <stdio.h>

void swap(int *data,int pos1,int pos2){
	int tmp=*(data+pos1);
	*(data+pos1)=*(data+pos2);
	*(data+pos2)=tmp;
}

void selectsort(int *data,int size){
	int min,minpos=-1;
	int i,j;
	for(i=0;i<size-1;i++){
		min=*(data+i);
		minpos=i;
		for(j=i+1;j<size;j++)
			if(*(data+j)<min){
				min=*(data+j);
				minpos=j;
			}
		if(minpos!=i)
			swap(data,i,minpos);
	}
}

void displayoutcome(int *data,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", *(data+i));
	printf("\n");
}

int main(){
	/*
	时间复杂度:O(n^2)
	空间复杂度:O(1)
	思路:对于每个位置，依次选出此位置到尾端之间最小的数，然后放在当前位置。
	*/
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,};
	int size=sizeof(data)/sizeof(int);
	selectsort(data,size);
	displayoutcome(data,size);
	return 0;
}