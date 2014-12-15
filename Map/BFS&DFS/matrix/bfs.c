#include <stdio.h>
#include "map.h"
#define QSIZE 100
#define N 100

int head,rear;
int queue[QSIZE];
int empty(void){
	return head==rear;
}
int full(void){
	return head==(rear+1)%rear;
}
void enqueue(int new){
	queue[rear]=new;
	rear=(rear+1)%QSIZE;
}
int dequeue(void){
	int retval=queue[head];
	head=(head+1)%QSIZE;
	return retval;
}

void breath_first_search_connected(int **map,int nodesize,int startnode,int *visited){
	enqueue(startnode);
	int cur,i;
	while(!empty()){
		cur=dequeue();
		if(!visited[cur]){
			visited[cur]=1;
			printf("%d ",cur);
		}
		for(i=0;i<nodesize;i++)
			if(map[cur][i] && !visited[i])
				enqueue(i);
	}
	printf("\n");
}

void breath_first_search(int **map,int nodesize){
	int i;
	int visited[N]={};
	for(i=0;i<nodesize;i++)
		if(!visited[i])
			breath_first_search_connected(map,nodesize,i,visited);
}

int main(int argc, char const *argv[])
{
	if(argc==1){
		printf("argv NULL!\n");
		return (1);
	}
	int nodesize;
	int **map=read_map(argv[1],&nodesize);
	display_debug(map,nodesize);
	breath_first_search(map,nodesize);
	return 0;
}