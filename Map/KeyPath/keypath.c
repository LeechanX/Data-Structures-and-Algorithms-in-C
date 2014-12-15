#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "map.h"

#define STACKSIZE 100
#define PRINT(x,size) printf("" #x ":");\
for(int i=0;i<size;i++)printf("%d ",x[i]);\
printf("\n");

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

int tsp=-1;
int topo_r[100];

struct Node *ifneiborOK(struct Graph *map,int i,int *visited){
	struct Node *retval=NULL,*cur=map->nodes[i]->next;
	while(cur && !retval){
		if(!visited[cur->vertex])
			retval=cur;
		cur=cur->next;
	}
	return retval;
}

void DFS_connect(struct Graph *map,int startnode,int *visited){
	push(startnode);
	visited[startnode]=1;
	//printf("%d ",startnode );
	int curno;
	struct Node *cur;
	while(!empty()){
		curno=top();
		if((cur=ifneiborOK(map,curno,visited))){
			push(cur->vertex);
			//printf("%d ",cur->vertex);
			visited[cur->vertex]=1;
		}else{
			pop();
			topo_r[++tsp]=curno;
		}
	}
}

void DFS(struct Graph *map){
	int visited[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		visited[i]=0;
	for(int i=0;i<map->nodesize;i++)
		if(!visited[i])
			DFS_connect(map,i,visited);
	//printf("\n");
}

int *count_ve(struct Graph *map,int *topo_r){
	int *ve=malloc(sizeof(int)*map->nodesize);
	for(int i=0;i<map->nodesize;i++)
		ve[i]=0;
	int nodeid;
	struct Node *cur=NULL;
	for(int i=tsp;i>=0;i--){
		nodeid=topo_r[i];
		cur=map->nodes[nodeid]->next;
		while(cur){
			//nodeid===>cur->vertex
			if(ve[nodeid]+cur->weight>ve[cur->vertex])
				ve[cur->vertex]=ve[nodeid]+cur->weight;
			cur=cur->next;
		}
	}
	return ve;
}

int *count_vl(struct Graph *map,int *topo_r,int *ve){
	int *vl=malloc(sizeof(int)*map->nodesize);
	int nodeid;
	struct Node *cur=NULL;
	for(int i=0;i<=tsp;i++)
		vl[i]=INT_MAX;
	vl[topo_r[0]]=ve[topo_r[0]];
	for(int i=0;i<=tsp;i++){
		nodeid=topo_r[i];
		cur=map->nodes[nodeid]->next;
		while(cur){
			// nodeid ===> cur->vertex
			if(vl[nodeid]>vl[cur->vertex]-cur->weight)
				vl[nodeid]=vl[cur->vertex]-cur->weight;
			cur=cur->next;
		}
	}
	return vl;
}

void count_keypath(struct Graph *map,int *ve,int *vl){
	struct Node *cur;
	for(int i=0;i<map->nodesize;i++){
		cur=map->nodes[i]->next;
		while(cur){
			//i===>cur->vertex
			if(ve[i]==vl[cur->vertex]-cur->weight)
				printf("%d==>%d\n",i,cur->vertex);
			cur=cur->next;
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	display_debug(map);
	DFS(map);
	int *ve=count_ve(map,topo_r);
	int *vl=count_vl(map,topo_r,ve);
	//PRINT(ve,map->nodesize);
	//PRINT(vl,map->nodesize);
	count_keypath(map,ve,vl);
	return 0;
}