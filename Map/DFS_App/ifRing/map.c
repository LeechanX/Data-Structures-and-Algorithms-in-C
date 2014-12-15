#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void graph_insertedge(struct Graph *map,int nodename1,int nodename2){
	struct Node *node=map->nodes[nodename1];
	struct Node *new=malloc(sizeof(struct Node));
	new->vertex=nodename2;
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
			printf(" %d",cur->vertex);
			cur=cur->next;
		}
		printf("\n");
	}
}

struct Graph *read_map(char const *filename,int *directed){
	FILE *map_file=fopen(filename,"r");
	int nodesize;
	fscanf(map_file,"%d %d\n",directed,&nodesize);
	struct Graph *map=graph_init(nodesize);
	char buff[1024];
	char *node_line=fgets(buff,sizeof(buff),map_file);
	char *node=strtok(node_line," \n");
	while(node){
		graph_insertnode(map,atoi(node));
		node=strtok(NULL," \n");
	}
	char *edge_line;
	int node1,node2;
	while((edge_line=fgets(buff,sizeof(buff),map_file))){
		node=strtok(edge_line,"\t\n");
		node1=atoi(node);
		node=strtok(NULL,"\t\n");
		node2=atoi(node);
		graph_insertedge(map,node1,node2);
		if(!*directed)
			graph_insertedge(map,node2,node1);
	}
	fflush(map_file);
	fclose(map_file);
	return map;	
}