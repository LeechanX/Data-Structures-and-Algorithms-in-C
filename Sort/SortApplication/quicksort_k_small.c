#include <stdio.h>
#include <stdlib.h>

void swap(int *data,int pos1,int pos2){
	int tmp=data[pos1];
	data[pos1]=data[pos2];
	data[pos2]=tmp;
}

void quicksplit_findtopk(int *data,int head,int rear,int k){
	//找出最小的K个
	if(head>=rear)
		return;
	int pivot=data[rear-1];
	int i=head,j=rear-2;
	while(i<=j){
		while(i<=rear-2 && data[i]<pivot)
			i++;
		while(j>=0 && data[j]>=pivot)
			j--;
		if(i<j){
			swap(data,i,j);
		}
	}
	swap(data,i,rear-1);
	if(i>k)
		quicksplit_findtopk(data,head,i,k);
	else if(i<k)
		quicksplit_findtopk(data,i+1,rear,k);
	else{
		int j=0;
		while(j<i)
			printf("%d ",data[j++]);
		printf("\n");
	}
}

void quicksplit_find_kth_min(int *data,int head,int rear,int k){
	if(head>=rear)
		return;
	int pivot=data[rear-1];
	int i=head,j=rear-2;
	while(i<=j){
		while(i<=rear-2 && data[i]<pivot)
			i++;
		while(j>=0 && data[j]>=pivot)
			j--;
		if(i<j)
			swap(data,i,j);
	}
	swap(data,i,rear-1);
	if(i>k-1)
		quicksplit_find_kth_min(data,head,i,k);
	else if(i<k-1)
		quicksplit_find_kth_min(data,i+1,rear,k);
	else
		printf("%dth minest number=%d\n",k,pivot);
}

int main(int argc, char const *argv[])
{
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,};
	int size=sizeof(data)/sizeof(int);
	int k=atoi(argv[1]);
	if(k>size)
		k=size;
	quicksplit_find_kth_min(data,0,size,k);
	if(k==size)
		k--;
	printf("top%d minest numbers:\n",k);
	quicksplit_findtopk(data,0,size,k);
	return 0;
}