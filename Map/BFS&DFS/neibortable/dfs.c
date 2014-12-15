#include <stdio.h>
#include "map.h"
#define STACKSIZE 100
#define N 100

void depth_first_search_conneted_recursive(struct Graph *map,int i,int *visited){
	if(visited[i])
		return;
	struct Node *node=map->nodes[i];
	printf("%d ",node->vertex);
	visited[i]=1;
	struct Node *cur=node->next;
	while(cur){
		depth_first_search_conneted_recursive(map,cur->vertex,visited);
		cur=cur->next;
	}
}

struct Node * stack[STACKSIZE];
int sp=-1;
int empty(void){
	return sp==-1;
}
void push(struct Node *item){
	stack[++sp]=item;
}
struct Node * pop(void){
	return stack[sp--];
}
struct Node * top(void){
	return stack[sp];
}

struct Node *unvisited_neibor(struct Graph *map,int i,int *visited){
	struct Node *cur=map->nodes[i]->next,*retval=NULL;
	while(cur){
		if(!visited[cur->vertex]){
			retval=cur;
			break;
		}
		cur=cur->next;
	}
	return retval;
}

void depth_first_search_conneted_nor_recursive(struct Graph *map,int startnode,int *visited){
	struct Node *cur=map->nodes[startnode];
	printf("%d ",cur->vertex);
	visited[cur->vertex]=1;
	push(cur);
	while(!empty()){
		cur=top();
		if((cur=unvisited_neibor(map,cur->vertex,visited))){
			printf("%d ",cur->vertex);
			visited[cur->vertex]=1;
			push(cur);
		}else{
			pop();
		}
	}
	printf("\n");
}

void depth_first_search_conneted_nor_recursive_cool(struct Graph *map,int startnode,int *visited){
	struct Node *cur=map->nodes[startnode];
	push(cur);
	while(!empty()){
		cur=pop();
		if(visited[cur->vertex])
			continue;
		visited[cur->vertex]=1;
		printf("%d ",cur->vertex );
		cur=map->nodes[cur->vertex]->next;
		while(cur){
			if(!visited[cur->vertex])
				push(cur);
			cur=cur->next;
		}
		//now...
	}
	printf("\n");
}

void depth_first_search(struct Graph *map){
	int visited[N]={};
	int i;
	for(i=0;i<map->nodesize;i++)
		if(!visited[i])
			//depth_first_search_conneted_recursive(map,i,visited);
			//depth_first_search_conneted_nor_recursive(map,i,visited);
			depth_first_search_conneted_nor_recursive_cool(map,i,visited);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	if(argc==1){
		printf("argv NULL!\n");
		return (1);
	}
	struct Graph *map=read_map(argv[1]);
	display_debug(map);
	depth_first_search(map);
	return 0;
}