#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE(array) sizeof array/sizeof *array

void swap(int *data,int pos1,int pos2){
	int tmp=data[pos1];
	data[pos1]=data[pos2];
	data[pos2]=tmp;
}

void heap_hold(int *data,int heapsize,int pos){
	int left=(pos<<1)+1,right=(pos<<1)+2,minpos=pos;
	if(right<heapsize && data[right]<data[minpos])
		minpos=right;
	if(left<heapsize && data[left]<data[minpos])
		minpos=left;
	if(minpos!=pos){
		swap(data,minpos,pos);
		heap_hold(data,heapsize,minpos);
	}
}

void init_heap(int *data,int heapsize){
	int lasthasleaf=(heapsize>>1)-1;
	for(int i=lasthasleaf;i>=0;i--)
		heap_hold(data,heapsize,i);
}

int delete_min(int *data,int *heapsize){
	int top=data[0];
	swap(data,0,*heapsize-1);
	*heapsize=*heapsize-1;
	heap_hold(data,*heapsize,0);
	return top;
}

int main(){
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,
	},size=ARRAYSIZE(data),heapsize=size;
	
	//create heap
	init_heap(data,heapsize);
	//get min
	for(int i=0;i<size;i++)
		delete_min(data,&heapsize);	
	//printf
	for(int i=size-1;i>=0;i--)
		printf("%d ",data[i]);
	printf("\n");
}
