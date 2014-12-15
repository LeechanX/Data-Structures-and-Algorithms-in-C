#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define START 0

#include "map.h"


int bellmanford(struct Graph *map){
	int shortestpath[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		shortestpath[i]=SHRT_MAX;
	shortestpath[START]=0;
	struct Node *cur;
	for(int i=0;i<map->nodesize-1;i++)
		for(int j=0;j<map->nodesize;j++){
			cur=map->nodes[j]->next;
			while(cur){
				//j ---> cur->vertex
				if(shortestpath[cur->vertex]>shortestpath[j]+cur->weight)
					shortestpath[cur->vertex]=shortestpath[j]+cur->weight;
				cur=cur->next;
			}
		}

	for(int i=0;i<map->nodesize;i++){
		cur=map->nodes[i]->next;
		while(cur){
			//j ---> cur->vertex
			if(shortestpath[cur->vertex]>shortestpath[i]+cur->weight)
				return 0;
			cur=cur->next;
		}
	}

	for(int i=0;i<map->nodesize;i++)
		printf("%d:%d\n",i,shortestpath[i]);
	return 1;
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	
	struct Graph *map=read_map(argv[1]);

	bellmanford(map);

	return 0;
}