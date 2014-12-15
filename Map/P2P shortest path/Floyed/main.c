#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "map.h"

void floyed(int **map,int nodesize,int **distance,int **prev){
	for(int k=0;k<nodesize;k++)
		for(int i=0;i<nodesize;i++)
			for(int j=0;j<nodesize;j++)
				if(distance[i][k]+distance[k][j]<distance[i][j])
					distance[i][j]=distance[i][k]+distance[k][j],prev[i][j]=prev[k][j];
}

int sp=-1;
int stack[100];
int empty(void){
	return sp==-1;
}
void push(int new){
	stack[++sp]=new;
}
int pop(void){
	return stack[sp--];
}

void print_path(int **prev,int nodesize,int source,int dest){
	push(dest);
	while(prev[source][dest]!=-1){
		dest=prev[source][dest];
		push(dest);
	}
	while(!empty())
		printf("==>%d",pop());
	printf("\n");
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	int nodesize;
	int **map=read_map(argv[1],&nodesize);

	int **distance=malloc(sizeof(int *)*nodesize);
	int **prev=malloc(sizeof(int *)*nodesize);
	for(int i=0;i<nodesize;i++){
		distance[i]=malloc(sizeof(int)*nodesize);
		prev[i]=malloc(sizeof(int)*nodesize);
		for(int j=0;j<nodesize;j++){
			if(i!=j && !map[i][j])
				map[i][j]=SHRT_MAX;
			distance[i][j]=map[i][j];
			prev[i][j]=-1;
			if(map[i][j])
				prev[i][j]=i;
		}
	}
	floyed(map,nodesize,distance,prev);
	display_debug(distance,nodesize);
	printf("prev:\n");
	display_debug(prev,nodesize);
	int test1,test2;
	while(scanf("%d%d",&test1,&test2)==2){
		printf("%d->%d shortest path length=:%d\n",test1,test2,distance[test1][test2]);
		print_path(prev,nodesize,test1,test2);
	}
	return 0;
}