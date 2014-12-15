#include "map.h"
#define QSIZE 100

int head,rear;
int queue[QSIZE];
int empty(void){
	return head==rear;
}
void enqueue(int item){
	queue[rear]=item;
	rear=(rear+1)%QSIZE;
}
int dequeue(void){
	int retval=queue[head];
	head=(head+1)%QSIZE;
	return retval;
}

void allshortestpath(struct Graph *map,int start,int end){
	int 
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	display_debug(map);

	return 0;
}