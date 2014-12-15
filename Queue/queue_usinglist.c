#include <stdio.h>
#include <stdlib.h>

struct List{
	int item;
	struct List *next;
};

struct Queue{
	int size;
	struct List *head;
	struct List *rear;
};
typedef struct Queue *qlink;

qlink create_queue(void){
	qlink queue=malloc(sizeof(struct Queue));
	if(!queue)
		return queue;
	queue->size=0;
	queue->head=queue->rear=NULL;
	return queue;
}

int empty(qlink queue){
	return queue->size==0;
}

void enqueue(qlink queue,int item){
	struct List *new=malloc(sizeof(struct List));
	if(!new)
		return;
	new->item=item;
	new->next=NULL;
	if(queue->head)
		queue->rear->next=new;
	else
		queue->head=new;
	queue->rear=new;
	queue->size++;
}

int dequeue(qlink queue){
	if(empty(queue))
		return -1;
	int retval=queue->head->item;
	struct List *torm=queue->head;
	if(queue->head==queue->rear)
		queue->rear=NULL;
	queue->head=queue->head->next;
	free(torm);
	queue->size--;
	return retval;
}

int main(){
	int data[]={1,2,3,4,5,6,7,8,9,10};
	int i=0;
	qlink queue=create_queue();
	while(i<5)
		enqueue(queue,data[i++]);
	while(!empty(queue))
		printf("%d\n",dequeue(queue) );
	while(i<10)
		enqueue(queue,data[i++]);
	while(!empty(queue))
		printf("%d\n",dequeue(queue) );
	return 0;
}