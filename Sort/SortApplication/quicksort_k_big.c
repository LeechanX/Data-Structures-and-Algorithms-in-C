#include <stdio.h>
#include <stdlib.h>
#define N 50

void swap(int *data,int pos1,int pos2){
	int tmp=data[pos1];
	data[pos1]=data[pos2];
	data[pos2]=tmp;
}

void quicksplit_findtopk(int *data,int head,int rear,int k){
	//找出最大的K个
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
	if(k>N-i-1)
		quicksplit_findtopk(data,head,i,k);
	else if(k<N-i-1)
		quicksplit_findtopk(data,i+1,rear,k);
	else{
		int j=i+1;
		while(j<N)
			printf("%d ",data[j++]);
		printf("\n");
	}
}

void quicksplit_find_kth_max(int *data,int head,int rear,int k){
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
	if(k>N-i)
		quicksplit_find_kth_max(data,head,i,k);
	else if(k<N-i)
		quicksplit_find_kth_max(data,i+1,rear,k);
	else
		printf("%dth maxest number=%d\n",k,pivot);
}

int main(int argc, char const *argv[])
{
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,};
	
	int k=atoi(argv[1]);
	if(k>N)
		k=N;
	quicksplit_find_kth_max(data,0,N,k);
	if(k==N)
		k--;
	printf("top%d maxest numbers:\n",k);
	quicksplit_findtopk(data,0,N,k);
	return 0;
}