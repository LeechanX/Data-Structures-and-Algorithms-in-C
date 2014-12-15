#include <stdio.h>
#include "map.h"
#define QSIZE 100
#define N 100

int head,rear;
struct Node * queue[QSIZE];
int empty(void){
	return head==rear;
}
int full(void){
	return head=(rear+1)%QSIZE;
}
void enqueue(struct Node *item){
	queue[rear]=item;
	rear=(rear+1)%QSIZE;
}
struct Node *dequeue(void){
	struct Node *retval=queue[head];
	head=(head+1)%QSIZE;
	return retval;
}

void breath_first_search_conneted(struct Graph *map,int start,int *visited){
	struct Node *startnode=map->nodes[start];
	enqueue(startnode);
	struct Node *cur;
	while(!empty()){
		cur=dequeue();
		if(!visited[cur->vertex]){
			cur=map->nodes[cur->vertex];
			printf("%d ",cur->vertex);
			visited[cur->vertex]=1;
			cur=cur->next;
			while(cur){
				if(!visited[cur->vertex])
					enqueue(map->nodes[cur->vertex]);
				cur=cur->next;
			}
		}
	}
	printf("\n");
}

void breath_first_search(struct Graph *map){
	int visited[N]={};
	int i;
	for(i=0;i<map->nodesize;i++)
		if(!visited[i])
			breath_first_search_conneted(map,i,visited);
}

int main(int argc, char const *argv[])
{
	struct Graph *map=read_map(argv[1]);
	display_debug(map);
	breath_first_search(map);
	return 0;
}