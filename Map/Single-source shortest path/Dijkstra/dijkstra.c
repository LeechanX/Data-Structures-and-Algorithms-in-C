#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "map.h"

#define START 0

struct Table{
	int prev;
	int distance;
	char known;
};

struct Table **init_table(int size){
	struct Table **table=malloc(sizeof(struct Table *)*size);
	for(int i=0;i<size;i++){
		table[i]=malloc(sizeof(struct Table));
		table[i]->known=0;
		table[i]->prev=-1;
		table[i]->distance=SHRT_MAX;
	}
	table[START]->distance=0;
	return table;
}

int find_entry(struct Table **table,int size){
	int pos=-1;
	int min=SHRT_MAX;
	for(int i=0;i<size;i++)
		if(!table[i]->known && table[i]->distance<min){
			min=table[i]->distance;
			pos=i;
		}
	return pos;
}

void dijkstra(struct Graph *map,struct Table **table){
	int pos;
	struct Node *cur;
	while((pos=find_entry(table,map->nodesize))!=-1){
		cur=map->nodes[pos]->next;
		while(cur){
			//pos --> cur->vertex
			if(table[cur->vertex]->distance>table[pos]->distance+cur->weight){
				table[cur->vertex]->distance=table[pos]->distance+cur->weight;
				table[cur->vertex]->prev=pos;
			}
			cur=cur->next;
		}
		table[pos]->known=1;
	}
}

void show_path(struct Table **table,int dest){
	int prev;
	while((prev=table[dest]->prev)!=-1){
		printf("%d<==",dest);
		dest=prev;
	}
	printf("%d\n",START);
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	struct Table **table=init_table(map->nodesize);
	dijkstra(map,table);
	for(int i=0;i<map->nodesize;i++)
		printf("%d,%d,%d\n",i,table[i]->distance,table[i]->prev);

	int source=START,dest;
	while(scanf("%d",&dest)==1){
		printf("%d到%d最短路径长为%d:\n",source,dest,table[dest]->distance);
		show_path(table,dest);
	}
	return 0;
}