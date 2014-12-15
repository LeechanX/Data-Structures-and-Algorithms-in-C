#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

int **graph_init(int nodesize){
	int **map=malloc(sizeof(int *)*nodesize);
	int i;
	for(i=0;i<nodesize;i++)
		*(map+i)=malloc(sizeof(int)*nodesize);
	return map;
}

void graph_insertedge(int **map,int nodename1,int nodename2){
	*(*(map+nodename1)+nodename2)=1;
}

void display_debug(int **map,int nodesize){
	int i,j;
	for(i=0;i<nodesize;i++){
		for(j=0;j<nodesize;j++)
			printf("%d ",*(*(map+i)+j));
		printf("\n");
	}
}

int **read_map(char const *filename,int *nodesize){
	FILE *map_file=fopen(filename,"r");
	int directed;
	fscanf(map_file,"%d %d\n",&directed,nodesize);
	int **map=graph_init(*nodesize);
	char buff[1024];
	char *node_line=fgets(buff,sizeof(buff),map_file);
	char *node=strtok(node_line," \n");
	while(node){
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
		if(!directed)
			graph_insertedge(map,node2,node1);
	}
	fflush(map_file);
	fclose(map_file);
	return map;	
}