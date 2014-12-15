#include <stdio.h>
//#define USE_NONRECURSIVE
#define USE_NONRECURSIVE

void swap(int *data,int pos1,int pos2){
	int tmp=*(data+pos1);
	*(data+pos1)=*(data+pos2);
	*(data+pos2)=tmp;
}

void quicksort_recursive(int *data,int head,int rear){
	if(head>=rear)
		return;
	int pivot=data[rear-1];
	int i=head,j=rear-2;
	while(i<=j){
		while(data[i]<pivot && i<rear)
			i++;
		while(data[j]>=pivot && j>=0)
			j--;
		if(i<j)
			swap(data,i,j);
	}
	swap(data,i,rear-1);
	quicksort_recursive(data,head,i);
	quicksort_recursive(data,i+1,rear);
}

int stack[1000];
int sp=-1;
void push(int item1,int item2){
	stack[++sp]=item1;
	stack[++sp]=item2;
}
int pop(){
	return stack[sp--];
}
int empty(){
	return sp==-1;
}

void quicksort_nonrecursive(int *data,int size){
	int head=0,rear=size;
	int i,j,pivot;
	push(head,rear);
	while(!empty()){
		rear=pop();
		head=pop();
		pivot=data[rear-1];
		i=head,j=rear-2;
		while(i<=j){
			while(i<rear && data[i]<pivot)
				i++;
			while(j>=0 && data[j]>=pivot)
				j--;
			if(i<j)
				swap(data,i,j);
		}
		swap(data,i,rear-1);
		if(head<i)
			push(head,i);
		if(i+1<rear)
			push(i+1,rear);
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
	quicksort_recursive(data,0,size);
	#elif defined(USE_NONRECURSIVE)
	printf("use non recursive\n");
	quicksort_nonrecursive(data,size);
	#endif
	displayoutcome(data,size);
	return 0;
}