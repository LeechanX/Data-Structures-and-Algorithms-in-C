#include <stdio.h>

void swap(int *data,int pos1,int pos2){
	int tmp=*(data+pos1);
	*(data+pos1)=*(data+pos2);
	*(data+pos2)=tmp;
}

void quicksort(int *data,int head,int rear){
	if(head>=rear)
		return ;
	int pivot=*(data+head);
	int first_bigger=head+1;
	for(int i=head;i<rear;i++)
		if(data[i] < pivot)
			swap(data,i,first_bigger++);
	swap(data,head,first_bigger-1);
	quicksort(data,head,first_bigger-1);
	quicksort(data,first_bigger,rear);
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
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,};
	int size=sizeof data/sizeof *data;
	quicksort(data,0,size);
	displayoutcome(data,size);
	return 0;
}