#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "map.h"

struct Graph *graph_init(int nodesize){
	struct Graph *map=malloc(sizeof(struct Graph));
	if(!map)
		return map;
	map->sp=0;
	map->nodesize=nodesize;
	map->nodes=malloc(sizeof(struct Node *)*nodesize);
	return map;
}

void graph_insertnode(struct Graph *map,int nodename){
	struct Node *newnode=malloc(sizeof(struct Node));
	newnode->next=NULL;
	newnode->vertex=nodename;
	map->nodes[map->sp++]=newnode;
}

void graph_insertedge(struct Graph *map,int nodename1,int nodename2,int weight){
	struct Node *node=map->nodes[nodename1];
	struct Node *new=malloc(sizeof(struct Node));
	new->vertex=nodename2;
	new->weight=weight;
	new->next=node->next;
	node->next=new;
}

void display_debug(struct Graph *map){
	int i;
	struct Node *cur;
	for(i=0;i<map->nodesize;i++){
		cur=map->nodes[i];
		printf("%d:",cur->vertex);
		cur=cur->next;
		while(cur){
			printf(" %d(%d)",cur->vertex,cur->weight);
			cur=cur->next;
		}
		printf("\n");
	}
}

