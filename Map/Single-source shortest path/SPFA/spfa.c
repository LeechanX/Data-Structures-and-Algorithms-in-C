#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define START 0

#include "map.h"

#define QSIZE 1000

int queue[QSIZE];
int head,rear;

int queueEmpty(void){
	return head==rear;
}

void enqueue(int new){
	queue[rear]=new;
	rear=(rear+1)%QSIZE;
}

int dequeue(void){
	int ret=queue[head];
	head=(head+1)%QSIZE;
	return ret;
}

int spfa(struct Graph *map){
	int shortestpath[map->nodesize],counter[map->nodesize];
	for(int i=0;i<map->nodesize;i++){
		shortestpath[i]=SHRT_MAX;
		counter[i]=0;
	}
	shortestpath[START]=0;
	enqueue(START);
	counter[START]++;
	struct Node *cur;
	int top;
	while(!queueEmpty()){
		top=dequeue();
		cur=map->nodes[top]->next;
		while(cur){
			if(shortestpath[top]+cur->weight < shortestpath[cur->vertex]){
				shortestpath[cur->vertex]=shortestpath[top]+cur->weight;
				enqueue(cur->vertex);
				counter[cur->vertex]++;
				if(counter[cur->vertex]==map->nodesize){
					printf("有负权回路\n");
					return 1;
				}
			}
			cur=cur->next;
		}
	}
	for(int i=0;i<map->nodesize;i++)
		printf("%d ", shortestpath[i]);
	printf("\n");
	return 0;
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	printf("%d\n",spfa(map) );
	return 0;
}