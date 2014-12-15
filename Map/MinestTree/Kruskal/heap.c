#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct Heap *init_heap(int size){
	struct Heap *heap=malloc(sizeof(struct Heap));
	heap->size=0;
	heap->data=malloc(sizeof(struct Edge *)*size);
	return heap;
}

void heap_swap(struct Heap *heap,int pos1,int pos2){
	struct Edge *tmp=heap->data[pos1];
	heap->data[pos1]=heap->data[pos2];
	heap->data[pos2]=tmp;
}

void heap_hold(struct Heap *heap,int pos){
	int minpos=pos;
	int left=2*pos+1,right=2*pos+2;
	if(left<heap->size && heap->data[left]->weight<heap->data[minpos]->weight)
		minpos=left;
	if(right<heap->size && heap->data[right]->weight<heap->data[minpos]->weight)
		minpos=right;
	if(minpos!=pos){
		heap_swap(heap,pos,minpos);
		heap_hold(heap,minpos);
	}
}

void heap_insert(struct Heap *heap,int node1,int node2,int weight){
	struct Edge *edge=malloc(sizeof(struct Edge));
	edge->node1=node1,edge->node2=node2,edge->weight=weight;
	heap->data[heap->size]=edge;
	heap->size++;
	if(heap->size==1)
		return;
	int current=heap->size-1,parentpos=(current+1)/2-1;
	while(parentpos>=0){
		if(heap->data[parentpos]->weight<=heap->data[current]->weight)
			break;
		heap_swap(heap,current,parentpos);
		current=parentpos;
		parentpos=(current+1)/2-1;
	}
}

struct Edge *delete_min(struct Heap *heap){
	if(!heap->size)
		return NULL;
	struct Edge *retval=heap->data[0];
	heap->data[0]=heap->data[heap->size-1];
	heap->size--;
	heap_hold(heap,0);
	return retval;
}