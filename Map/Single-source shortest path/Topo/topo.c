#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define STACKSIZE 100

#include "map.h"

int sp=-1;
int stack[STACKSIZE];
int empty(void){
	return sp==-1;
}
void push(int new){
	stack[++sp]=new;
}
int pop(void){
	return stack[sp--];
}
int top(void){
	return stack[sp];
}

void DFS_connect(struct Graph *map,int startnode,int *visited){
	if(visited[startnode])
		return;
	struct Node *cur=map->nodes[startnode]->next;
	while(cur){
		if(!visited[cur->vertex])
			DFS_connect(map,cur->vertex,visited);
		cur=cur->next;
	}
	visited[startnode]=1;
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

void topo(struct Graph *map){
	#define START 1
	DFS(map);
	int curno;
	int shortestpath[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		shortestpath[i]=SHRT_MAX;
	shortestpath[START]=0;
	struct Node *cur;
	while(!empty() && top()!=START)
		pop();
	while(!empty()){
		curno=pop();
		cur=map->nodes[curno]->next;
		while(cur){
			if(shortestpath[cur->vertex]>shortestpath[curno]+cur->weight)
				shortestpath[cur->vertex]=shortestpath[curno]+cur->weight;
			cur=cur->next;
		}
	}
	for(int i=0;i<map->nodesize;i++)
		printf("%d,%d\n",i,shortestpath[i]);
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	topo(map);
	return 0;
}