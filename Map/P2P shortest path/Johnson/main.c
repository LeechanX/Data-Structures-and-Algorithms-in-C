#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "map.h"

int bellman_ford(struct Graph *map,int *distance,int source){
	struct Node *cur;
	for(int i=0;i<map->nodesize-1;i++)
		for(int j=0;j<map->nodesize;j++){
			cur=map->nodes[j]->next;
			while(cur){
				//i=>cur->vertex
				if(distance[j]+cur->weight<distance[cur->vertex])
					distance[cur->vertex]=distance[j]+cur->weight;
				cur=cur->next;
			}
		}
	int ok=1;
	for(int i=0;i<map->nodesize && ok;i++){
		cur=map->nodes[i]->next;
		while(cur && ok){
			//i=>cur->vertex
			if(distance[i]+cur->weight<distance[cur->vertex])
				ok=0;
			cur=cur->next;
		}
	}
	return ok;
}

void change2positive(struct Graph *map,int *distance){
	map->nodes=realloc(map->nodes,sizeof(struct Node *)*(map->nodesize+1));
	int source=map->nodesize;
	graph_insertnode(map,source);
	map->nodesize++;
	for(int i=0;i<source;i++)
		graph_insertedge(map,source,i,0);
	//display_debug(map);
	distance[source]=0;
	int status=bellman_ford(map,distance,source);
	if(!status)
		return;
	struct Node *cur;
	for(int i=0;i<map->nodesize;i++){
		cur=map->nodes[i]->next;
		while(cur){
			//i => cur->vertex
			cur->weight+=distance[i]-distance[cur->vertex];
			cur=cur->next;
		}
	}
	display_debug(map);
	map->nodesize--;
}

int find_min_d_dij(int *distance,int size,int *known){
	int retval=-1,min=SHRT_MAX;
	for(int i=0;i<size;i++)
		if(!known[i] && distance[i]<min){
			min=distance[i];
			retval=i;
		}
	return retval;
}

void dijkstra(struct Graph *map,int source,int *h,int *distance){
	distance[source]=0;
	int known[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		known[i]=0;
	int find;
	struct Node *cur;
	while((find=find_min_d_dij(distance,map->nodesize,known))!=-1){
		known[find]=1;
		cur=map->nodes[find]->next;
		while(cur){
			//find=>cur->vertex
			if(distance[find]+cur->weight<distance[cur->vertex])
				distance[cur->vertex]=distance[find]+cur->weight;
			cur=cur->next;
		}
	}
}

void johnson(struct Graph *map,int *h){
	int **retval=malloc(sizeof(int *)*map->nodesize);
	for(int i=0;i<map->nodesize;i++){
		retval[i]=malloc(sizeof(int)*map->nodesize);
		for(int j=0;j<map->nodesize;j++)
			retval[i][j]=SHRT_MAX;
	}
	printf("source");
	for(int i=0;i<map->nodesize;i++)
		printf("\t%d",i);
	printf("\n");
	for(int i=0;i<map->nodesize;i++){
		dijkstra(map,i,h,retval[i]);
		printf("%d",i);
		for(int j=0;j<map->nodesize;j++){
			//node=j,source=i
			retval[i][j]+=h[j]-h[i];
			printf("\t%d",retval[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	int hasnegativeweight=0;
	FILE *map_file=fopen(argv[1],"r");
	int directed,nodesize;
	fscanf(map_file,"%d %d\n",&directed,&nodesize);
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
		if(!hasnegativeweight && weight<0)
			hasnegativeweight=1;
		graph_insertedge(map,node1,node2,weight);
		if(!directed)
			graph_insertedge(map,node2,node1,weight);
	}
	fflush(map_file);
	fclose(map_file);

	//display_debug(map);
	int *distance=malloc(sizeof(int)*(map->nodesize+1));
	for(int i=0;i<map->nodesize;i++)
		distance[i]=SHRT_MAX;
	if(hasnegativeweight)
		change2positive(map,distance);
	johnson(map,distance);
	return 0;
}