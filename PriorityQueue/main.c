#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PriorityQueue.h"
#define HEAPSIZE 100

int main(){
	struct Task *task;
	int priority,i;
	srand(time(NULL));
	heaptype heap=create_heap(HEAPSIZE);
	for(i=0;i<10;i++){
		priority=i*i;//rand()%100;
		task=create_task(i,priority);
		insert_heap(heap,task);
	}
	increase_priority(heap,3,1000);
	if((task=delete_min(heap))){
		printf("taskid=%d,task priority=%d\n",task->taskid,task->priority);
		decrease_priority(heap,4,3);
		increase_priority(heap,0,999);
	}
	increase_priority(heap,1,28);
	while((task=delete_min(heap)))
		printf("taskid=%d,task priority=%d\n",task->taskid,task->priority);
	destroy_heap(heap);
}
