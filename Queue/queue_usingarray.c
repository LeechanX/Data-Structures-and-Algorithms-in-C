#include <stdio.h>
#include <stdlib.h>

struct Queue{
	int capibility;
	int *data;
	int head;
	int rear;
};
typedef struct Queue *qlink;

qlink create_queue(int capibility){
	qlink queue=malloc(sizeof(struct Queue));
	if(!queue)
		return queue;
	queue->capibility=capibility;
	queue->data=malloc(sizeof(int)*capibility);
	queue->head=queue->rear=0;
	return queue;
}

int full(qlink queue){
	return queue->head==(queue->rear+1)%queue->capibility;
}

int empty(qlink queue){
	return queue->head==queue->rear;
}

void enqueue(qlink queue,int item){
	if(full(queue))
		return;
	queue->data[queue->rear]=item;
	queue->rear=(queue->rear+1)%queue->capibility;
}

int dequeue(qlink queue){
	if(empty(queue))
		return -1;
	int retval=queue->data[queue->head];
	queue->head=(queue->head+1)%queue->capibility;
	return retval;
}

int main(){
	int data[]={1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18};
	int i=0;
	qlink queue=create_queue(8);
	while(i<5)
		enqueue(queue,data[i++]);
	while(!empty(queue))
		printf("%d\n",dequeue(queue) );
	while(i<18 && !full(queue))
		enqueue(queue,data[i++]);
	while(!empty(queue))
		printf("%d\n",dequeue(queue) );
	return 0;
}