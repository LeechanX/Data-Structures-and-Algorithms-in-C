#include <stdio.h>
#include <stdlib.h>

struct Heap{
	int capability;
	int size;
	int *data;
};

struct Heap *create_heap(int capability){
	struct Heap *heap=malloc(sizeof(struct Heap));
	if(!heap)
		return heap;
	heap->capability=capability;
	heap->size=0;
	heap->data=malloc(sizeof(int)*capability);
	return heap;
}

int heap_full(struct Heap *heap){
	return heap->capability==heap->size;
}

int heap_empty(struct Heap *heap){
	return heap->size==0;
}

void heap_swap(struct Heap *heap,int pos1,int pos2){
	int tmp=heap->data[pos1];
	heap->data[pos1]=heap->data[pos2];
	heap->data[pos2]=tmp;
}

void heap_hold(struct Heap *heap,int pos){
	int max=heap->data[pos],maxpos=pos;
	int left=2*pos+1,right=2*pos+2;
	if(left<heap->size && heap->data[left]>max){
		max=heap->data[left];
		maxpos=left;
	}
	if(right<heap->size && heap->data[right]>max)
		maxpos=right;
	if(maxpos!=pos){
		heap_swap(heap,maxpos,pos);
		heap_hold(heap,maxpos);
	}
}

void insert_heap(struct Heap *heap,int item){
	if(heap_full(heap)){
		int top=heap->data[0];
		if(item<top){
			heap->data[0]=item;
			heap_hold(heap,0);
		}
	}else{
		int current,parent;
		heap->data[heap->size]=item;
		current=heap->size;
		heap->size++;
		parent=(current+1)/2-1;
		while(parent>=0 && heap->data[parent]<heap->data[current]){
			heap_swap(heap,parent,current);
			current=parent;
			parent=(current+1)/2-1;
		}
	}
}

int deletemax_heap(struct Heap *heap){
	if(heap_empty(heap))
		return -1;
	int retval=heap->data[0];
	heap_swap(heap,0,heap->size-1);
	heap->size--;
	if(!heap_empty(heap))
		heap_hold(heap,0);
	return retval;
}

int getmax_heap(struct Heap *heap){
	if(heap_empty(heap))
		return -1;
	return heap->data[0];
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
	//找出最小的K个
	struct Heap *heap=create_heap(k);
	int i=0;
	while(i<size)
		insert_heap(heap,data[i++]);
	printf("%dth smallest number=%d\n",k,getmax_heap(heap));
	printf("top%d smallest numbers:\n",k );
	while(!heap_empty(heap))
		printf("%d ", deletemax_heap(heap));
	printf("\n");
	return 0;
}