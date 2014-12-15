#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int findneinor_unvisited(struct Graph *map,int node,int *visited){
	struct Node *cur=map->nodes[node]->next;
	int retval=-1;
	while(cur){
		if(!visited[cur->vertex]){
			retval=cur->vertex;
			break;
		}
		cur=cur->next;
	}
	return retval;
}

void DFS_dg(struct Graph *map,int startnode,int *visited,int *flag){
	if(visited[startnode]==-1){
		*flag=1;
		return;
	}
	if(*flag==1 || visited[startnode])
		return;
	struct Node *cur=map->nodes[startnode]->next;
	visited[startnode]=-1;
	while(cur){
		DFS_dg(map,cur->vertex,visited,flag);
		cur=cur->next;
	}
	visited[startnode]=1;
}

int ifRing_dg(struct Graph *map){
	int visited[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		visited[i]=0;
	int flag=0;
	for(int i=0;i<map->nodesize && !flag;i++)
		DFS_dg(map,i,visited,&flag);
	return flag;
}

void DFS_udg(struct Graph *map,int startnode,int prev,int *visited,int *flag){
	if(visited[startnode]==-1){
		*flag=1;
		return;
	}
	if(*flag==1 || visited[startnode])
		return;
	struct Node *cur=map->nodes[startnode]->next;
	visited[startnode]=-1;
	while(cur){
		if(cur->vertex!=prev)
			DFS_udg(map,cur->vertex,startnode,visited,flag);
		cur=cur->next;
	}
	visited[startnode]=1;
}

int ifRing_udg(struct Graph *map){
	int visited[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		visited[i]=0;
	int flag=0;
	for(int i=0;i<map->nodesize && !flag;i++)
		DFS_udg(map,i,-1,visited,&flag);
	return flag;
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	int directed;
	struct Graph *map=read_map(argv[1],&directed);
	int status;
	status=directed?ifRing_dg(map):ifRing_udg(map);
	if(status)
		printf("有环\n");
	else
		printf("无环\n");
	return 0;
}