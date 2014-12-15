#include <stdio.h>
#include "map.h"
#define STACKSIZE 100
#define N 100

void depth_first_search_conneted_recursive(int **map,int startnode,int nodesize,int *visited){
	if(visited[startnode])
		return;
	visited[startnode]=1;
	printf("%d ",startnode);
	int i;
	for(i=0;i<nodesize;i++)
		if(map[startnode][i] && !visited[i])
			depth_first_search_conneted_recursive(map,i,nodesize,visited);
}

int stack[STACKSIZE];
int sp=-1;
int empty(void){
	return sp==-1;
}
void push(int item){
	stack[++sp]=item;
}
int pop(void){
	return stack[sp--];
}
int top(void){
	return stack[sp];
}

int unvisited_neibor(int **map,int i,int nodesize,int *visited){
	int j;
	for(j=0;j<nodesize;j++)
		if(!visited[j])
			return j;
	return -1;
}

void depth_first_search_conneted_nor_recursive(int **map,int startnode,int nodesize,int *visited){
	visited[startnode]=1;
	printf("%d ",startnode);
	push(startnode);
	int cur,neibor;
	while(!empty()){
		cur=top();
		if((neibor=unvisited_neibor(map,cur,nodesize,visited))!=-1){
			printf("%d ",neibor);
			visited[neibor]=1;
			push(neibor);
		}else
			pop();
	}
}

void depth_first_search(int **map,int nodesize){
	int visited[N]={};
	int i;
	for(i=0;i<nodesize;i++)
		if(!visited[i])
			//depth_first_search_conneted_recursive(map,i,nodesize,visited);
			depth_first_search_conneted_nor_recursive(map,i,nodesize,visited);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	if(argc==1){
		printf("argv NULL!\n");
		return (1);
	}
	int nodesize;
	int **map=read_map(argv[1],&nodesize);
	display_debug(map,nodesize);
	depth_first_search(map,nodesize);
	return 0;
}