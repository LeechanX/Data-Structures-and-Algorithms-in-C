#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "disjointset.h"
#include "heap.h"

void kruskal(struct Graph *map,struct Heap *heap,struct Set **origin_set){
	struct Graph *treemap=graph_init(map->nodesize);
	for(int i=0;i<map->nodesize;i++)
		graph_insertnode(treemap,i);
	
	struct Edge *cur;
	int node1,node2,weight;
	struct Set *par1,*par2;
	while((cur=delete_min(heap))){
		node1=cur->node1,node2=cur->node2,weight=cur->weight;
		par1=find_set(origin_set[node1]),par2=find_set(origin_set[node2]);
		
		if(par1!=par2){
			union_set(par1,par2);
			graph_insertedge(treemap,node1,node2,weight);
			graph_insertedge(treemap,node2,node1,weight);
		}
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

	struct Heap *heap=init_heap(edgesize);

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

		heap_insert(heap,node1,node2,weight);
		if(!directed)
			graph_insertedge(map,node2,node1,weight);
	}
	fflush(map_file);
	fclose(map_file);

	display_debug(map);
	struct Set **origin_set=init_set(map->nodesize);

	kruskal(map,heap,origin_set);

	return 0;
}