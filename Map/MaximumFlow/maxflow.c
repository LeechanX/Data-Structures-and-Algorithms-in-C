#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "map.h"
#define QSIZE 100

int **init_flow(int nodesize){
	int **flow=malloc(sizeof(int *)*nodesize);
	int i,j;
	for(i=0;i<nodesize;i++){
		flow[i]=malloc(sizeof(int)*nodesize);
		for(j=0;j<nodesize;j++)
			flow[i][j]=0;
	}
	return flow;
}

int **create_complegraph(int **capacity,int nodesize,int **flow){
	int **complegraph=malloc(sizeof(int *)*nodesize);
	int i,j;
	for(i=0;i<nodesize;i++)
		complegraph[i]=malloc(sizeof(int)*nodesize);
	for(i=0;i<nodesize;i++){
		for(j=0;j<nodesize;j++){
			if(capacity[i][j]-flow[i][j]>0)
				complegraph[i][j]=capacity[i][j]-flow[i][j];
			else
				complegraph[i][j]=0;
		}
	}
	return complegraph;
}

void destory_matrix(int **matrix,int size){
	int i;
	for(i=0;i<size;i++)
		free(matrix[i]);
	free(matrix);
}


int head,rear;
int queue[QSIZE];
int empty(void){
	return head==rear;
}
void enqueue(int new){
	queue[rear]=new;
	rear=(rear+1)%QSIZE;
}
int dequeue(void){
	int retval=queue[head];
	head=(head+1)%QSIZE;
	return retval;
}

#define START 0
#define END 5

int find_path(int **complegraph,int nodesize,int **flow){
	int prev[nodesize];
	int visited[nodesize];
	int i;
	for(i=0;i<nodesize;i++)
		visited[i]=0,prev[i]=-1;
	enqueue(START);
	int cur;
	while(!empty()){
		cur=dequeue();
		if(cur==END)
			break;
		if(!visited[cur]){
			visited[cur]=1;
			for(i=0;i<nodesize;i++)
				if(complegraph[cur][i] && !visited[i]){
					prev[i]=cur;
					enqueue(i);
				}
		}		
	}
	if(cur==END){
		int parent;
		int minflow=INT_MAX;
		while((parent=prev[cur])!=-1){
			if(complegraph[parent][cur]<minflow)
				minflow=complegraph[parent][cur];
			cur=parent;
		}
		cur=END;
		while((parent=prev[cur])!=-1){
			printf("%d->%d\n",parent,cur);
			flow[parent][cur]+=minflow;
			flow[cur][parent]-=minflow;
			cur=parent;
		}
		return 1;
	}else{
		return 0;
	}
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	int nodesize;
	int **capacity=read_map(argv[1],&nodesize);
	int **flow=init_flow(nodesize);
	display_debug(capacity,nodesize);

	int status=0;
	int **complegraph;

	do{
		complegraph=create_complegraph(capacity,nodesize,flow);
		status=find_path(complegraph,nodesize,flow);
		destory_matrix(complegraph,nodesize);
	}while(status);

	printf("maximum flow:\n");
	display_debug(flow,nodesize);

	return 0;
}