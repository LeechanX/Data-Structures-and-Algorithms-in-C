#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "map.h"
#define SOURCENODE 0

struct Table{
	char known;
	int distance;
	int prevnode;
};

struct Table **create_table(struct Graph *map){
	struct Table **table=malloc(sizeof(struct Table *)*map->nodesize);
	int i;
	for(i=0;i<map->nodesize;i++){
		table[i]=malloc(sizeof(struct Table));
		table[i]->known=0;
		table[i]->distance=INT_MAX;
		table[i]->prevnode=-1;
	}
	table[SOURCENODE]->distance=0;
	return table;
}

int find_startnode(struct Table **table,int size){
	int i;
	int retpos=-1,minvalue=INT_MAX;
	for(i=0;i<size;i++)
		if(!table[i]->known && table[i]->distance<minvalue){
			minvalue=table[i]->distance;
			retpos=i;
		}
	return retpos;
}


void prim(struct Graph *map){
	struct Table **table=create_table(map);
	int startnode;
	struct Node *cur;
	while((startnode=find_startnode(table,map->nodesize))!=-1){
		table[startnode]->known=1;
		cur=map->nodes[startnode]->next;
		while(cur){
			if(!table[cur->vertex]->known && cur->weight<table[cur->vertex]->distance){
				table[cur->vertex]->distance=cur->weight;
				table[cur->vertex]->prevnode=startnode;
			}
			cur=cur->next;
		}
	}
	struct Graph *treemap=graph_init(map->nodesize);
	for(int i=0;i<map->nodesize;i++)
		graph_insertnode(treemap,i);
	for(int i=1;i<map->nodesize;i++){
		graph_insertedge(treemap,table[i]->prevnode,i,table[i]->distance);
		graph_insertedge(treemap,i,table[i]->prevnode,table[i]->distance);
	}
	printf("Done.\n");
	printf("Minest Tree:\n");
	display_debug(treemap);
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;

	FILE *map_file=fopen(argv[1],"r");
	int directed,nodesize,edgesize;
	fscanf(map_file,"%d %d %d\n",&directed,&nodesize,&edgesize);
	struct Graph *map=graph_init(nodesize);

	char buff[1024];
	char *node_line=fgets(buff,sizeof(buff),map_file);
	char *node=strtok(node_line," \n");
	while(node){
		graph_insertnode(map,atoi(node));
		node=strtok(NULL," \n");
	}
	char *edge_line;
	int node1,node2,weight;
	while((edge_line=fgets(buff,sizeof(buff),map_file))){
		node=strtok(edge_line,"\t\n");
		node1=atoi(node);
		node=strtok(NULL,"\t\n");
		node2=atoi(node);
		node=strtok(NULL,"\t\n");
		weight=atoi(node);
		graph_insertedge(map,node1,node2,weight);
		if(!directed)
			graph_insertedge(map,node2,node1,weight);
	}
	fflush(map_file);
	fclose(map_file);

	display_debug(map);

	prim(map);

	return 0;
}