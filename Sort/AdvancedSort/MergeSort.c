#include <stdio.h>
#define USE_NONRECURSIVE
#define N 50

void merge(int *data,int head,int mid,int rear){
	int copydata[N],sp=-1;
	int i=head,j=mid;
	while(i<mid && j<rear)
		if(data[i]<=data[j])
			copydata[++sp]=data[i++];
		else
			copydata[++sp]=data[j++];
	while(i<mid)
		copydata[++sp]=data[i++];
	while(j<rear)
		copydata[++sp]=data[j++];
	for(i=head;i<rear;i++)
		data[i]=copydata[i-head];
}

void mergesort_recursive(int *data,int head,int rear){
	if(head>=rear-1)
		return;
	int mid=(head+rear)/2;
	mergesort_recursive(data,head,mid);
	mergesort_recursive(data,mid,rear);
	merge(data,head,mid,rear);
}

void mergesort_nonrecursive(int *data,int size){
	int subsize,i;
	int head,mid,rear;
	for(subsize=2;subsize<size*2;subsize*=2){
		for(i=0;i<size;i+=subsize){
			head=i;
			mid=head+subsize/2;
			rear=head+subsize;
			if(rear>size)
				rear=size;
			merge(data,head,mid,rear);
		}
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
	时间复杂度:O(n)
	空间复杂度:O()
	适用于属于一定范围内的数的排序。
	思路:。
	*/
	int data[]={60,2,97,78,0,84,68,23,48,22,63,31,43,42,82,9,
		57,21,42,62,83,98,64,72,96,31,76,13,70,49,10,60,72,36,
		26,4,56,54,13,9,98,45,61,90,88,80,30,50,77,83,};
	int size=sizeof data/sizeof *data;
	#ifdef USE_RECURSIVE
	printf("use recursive\n");
	mergesort_recursive(data,0,size);
	#elif defined(USE_NONRECURSIVE)
	printf("use non recursive\n");
	mergesort_nonrecursive(data,size);
	#endif
	displayoutcome(data,size);
	return 0;
}