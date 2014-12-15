#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>

#include "map.h"

struct Graph *graph_init(int nodesize){
	struct Graph *map=(struct Graph *)malloc(sizeof(struct Graph));
	if(!map)
		return map;
	map->sp=0;
	map->nodesize=nodesize;
	map->nodes=(struct Node **)malloc(sizeof(struct Node *)*nodesize);
	return map;
}

void graph_insertnode(struct Graph *map,int nodename){
	struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));
	newnode->next=NULL;
	newnode->vertex=nodename;
	map->nodes[map->sp++]=newnode;
}

void graph_insertedge(struct Graph *map,int nodename1,int nodename2){
	struct Node *node=map->nodes[nodename1];
	struct Node *newone=(struct Node *)malloc(sizeof(struct Node));
	newone->vertex=nodename2;
	newone->next=node->next;
	node->next=newone;
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

struct Graph *read_map(char const *filename,map <int,string> *node_hash){
	FILE *map_file=fopen(filename,"r");
	int directed,nodesize;
	fscanf(map_file,"%d %d\n",&directed,&nodesize);
	struct Graph *graph=graph_init(nodesize);
	char buff[1024];
	char *node_line=fgets(buff,sizeof(buff),map_file);
	char *node=strtok(node_line," \n");

	int i=0;
	while(node){
		(*node_hash)[i]=node;
		graph_insertnode(graph,i);
		node=strtok(NULL," \n");
		i++;
	}

	map <string,int> name2no;
	for(i=0;i<nodesize;i++)
		name2no[(*node_hash)[i]]=i;

	char *edge_line;
	int node1,node2;
	while((edge_line=fgets(buff,sizeof(buff),map_file))){
		node=strtok(edge_line,"\t\n");
		node1=name2no[node];
		node=strtok(NULL,"\t\n");
		node2=name2no[node];
		graph_insertedge(graph,node1,node2);
		if(!directed)
			graph_insertedge(graph,node2,node1);
	}
	fflush(map_file);
	fclose(map_file);
	return graph;	
}