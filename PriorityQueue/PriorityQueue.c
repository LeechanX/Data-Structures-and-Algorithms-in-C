#include <stdlib.h>
#include "PriorityQueue.h"

struct Task *create_task(int taskid,int priority){
	struct Task *task=malloc(sizeof(struct Task));
	if(task)
		task->taskid=taskid,task->priority=priority;
	return task;
}

void swap_heap(heaptype heap,int pos1,int pos2){
	struct Task *tmp=heap->data[pos1];
	heap->data[pos1]=heap->data[pos2];
	heap->data[pos2]=tmp;
}

heaptype create_heap(int capacity){
	heaptype heap=malloc(sizeof(struct Heap));
	if(!heap)
		return heap;
	heap->size=0,heap->capacity=capacity;
	heap->data=malloc(sizeof(struct Task *)*capacity);
	return heap;
}

int empty_heap(heaptype heap){
	return heap->size==0;
}

int full_heap(heaptype heap){
	return heap->size==heap->capacity;
}

int gettaskbyid(heaptype heap,int id){
	int pos=-1;
	for(int i=0;i<heap->size && pos==-1;i++)
		if(heap->data[i]->taskid==id)
			pos=i;
	return pos;
}

void hold_heap(heaptype heap,int pos){
	int left=(pos<<1)+1,right=(pos<<1)+2,minpos=pos;
	if(right<heap->size && heap->data[right]->priority > heap->data[minpos]->priority)
		minpos=right;
	if(left<heap->size && heap->data[left]->priority > heap->data[minpos]->priority)
		minpos=left;
	if(minpos!=pos){
		swap_heap(heap,minpos,pos);
		hold_heap(heap,minpos);
	}
}

void insert_heap(heaptype heap,struct Task *newtask){
	if(full_heap(heap))
		return ;
	heap->data[heap->size]=newtask;
	int currentpos=heap->size,parentpos;
	heap->size+=1;
	while((parentpos=(currentpos-1)>>1)>=0 && 
		heap->data[parentpos]->priority < heap->data[currentpos]->priority){
		swap_heap(heap,parentpos,currentpos);
		currentpos=parentpos;
	}
}

void decrease_priority(heaptype heap,int taskid,int priority){
	int where=gettaskbyid(heap,taskid);
	if(where==-1 || where>=heap->size || heap->data[where]->priority <= priority)
		return ;
	heap->data[where]->priority=priority;
	hold_heap(heap,where);
}

void increase_priority(heaptype heap,int taskid,int priority){
	int where=gettaskbyid(heap,taskid);
	if(where==-1 || where>=heap->size || heap->data[where]->priority >= priority)
		return ;
	int currentpos=where,parentpos;
	heap->data[where]->priority=priority;
	while((parentpos=(currentpos-1)>>1)>=0 && 
		heap->data[parentpos]->priority < heap->data[currentpos]->priority){
		swap_heap(heap,parentpos,currentpos);
		currentpos=parentpos;
	}
}

struct Task *delete_min(heaptype heap){
	if(empty_heap(heap))
		return NULL;
	struct Task *top=heap->data[0];
	swap_heap(heap,0,heap->size-1);
	heap->size-=1;
	hold_heap(heap,0);
	return top;
}

void destroy_heap(heaptype heap){
	free(heap->data);
	free(heap);
}
