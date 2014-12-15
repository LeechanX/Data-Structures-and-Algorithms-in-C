#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define START 4

int path[1000];
int sp;

void graph_deleteedge(struct Graph *map,int node,int neibor){
	struct Node *cur,*prev;
	prev=map->nodes[node];
	cur=prev->next;
	while(cur && cur->vertex!=neibor){
		prev=cur;
		cur=cur->next;
	}
	prev->next=cur->next;
	free(cur);
	prev=map->nodes[neibor];
	cur=prev->next;
	while(cur && cur->vertex!=node){
		prev=cur;
		cur=cur->next;
	}
	prev->next=cur->next;
	free(cur);
}

void DFS(struct Graph *map,int prev,int startnode){
	printf("%d\n",startnode);
	path[sp++]=startnode;
	if(prev!=-1)
		graph_deleteedge(map,startnode,prev);
	struct Node *cur=map->nodes[startnode]->next;
	if(cur){
		DFS(map,startnode,cur->vertex);
	}
}

int find_new(struct Graph *map){
	for(int i=0;i<sp;i++)
		if(map->nodes[path[i]]->next)
			return i;
	return -1;
}

void draw(struct Graph *map){
	DFS(map,-1,START);
	int new;
	while((new=find_new(map))!=-1){
		printf("========\n");
		DFS(map,-1,path[new]);
	}
	printf("End\n");
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	//display_debug(map);
	draw(map);
	return 0;
}