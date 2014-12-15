#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define STACKSIZE 100

int sp=-1;
int stack[STACKSIZE];
int empty(void){
	return sp==-1;
}
void push(int new){
	stack[++sp]=new;
}
int pop(void){
	return stack[--sp];
}

void DFS_connect(struct Graph *map,int startnode,int *visited){
	if(visited[startnode])
		return;
	struct Node *cur=map->nodes[startnode]->next;
	printf("%d ",startnode );
	visited[startnode]=1;
	while(cur){
		DFS_connect(map,cur->vertex,visited);
		cur=cur->next;
	}
	push(startnode);
}

void DFS(struct Graph *map){
	int visited[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		visited[i]=0;
	for(int i=0;i<map->nodesize;i++)
		if(!visited[i])
			DFS_connect(map,i,visited);
}

struct Graph *reversegraph(struct Graph *map){
	struct Graph *rmap=graph_init(map->nodesize);
	struct Node *cur;
	for(int i=0;i<map->nodesize;i++)
		graph_insertnode(rmap,i);
	for(int i=0;i<map->nodesize;i++){
		cur=map->nodes[i]->next;
		while(cur){//i --> cur->vertex
			graph_insertedge(rmap,cur->vertex,i);
			cur=cur->next;
		}
	}
	return rmap;
}

void strongly_connect_comp(struct Graph *map){
	struct Graph *rmap=reversegraph(map);
	DFS(map);
	int curno;
	int rvisited[rmap->nodesize];
	for(int i=0;i<rmap->nodesize;i++)
		rvisited[i]=0;
	while(!empty()){
		curno=pop();
		if(!rvisited[curno]){
			printf("======\n");
			DFS_connect(rmap,curno,rvisited);
			printf("\n");
		}
			
	}
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	strongly_connect_comp(map);
	return 0;
}