#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODESIZE 5
#define STARTNODE 0

struct Node{
	int id;
	int cost;
	int height;
	struct Node *prev;
};
#define QSIZE 100
struct Node *stack[QSIZE];
int sp=-1;
int empty(void){
	return sp==-1;
}
void push(struct Node *item){
	stack[++sp]=item;
}
struct Node *pop(void){
	return stack[--sp];
}
struct Node *top(void){
	return stack[sp];
}

void insertsort(struct Node **nodes,int size){
	int i,j;
	struct Node *pivot;
	for(i=1;i<size;i++){
		pivot=nodes[i];
		for(j=i-1;j>=0 && nodes[j]->cost < pivot->cost;j--)
			nodes[j+1]=nodes[j];
		nodes[j+1]=pivot;
	}
}

int min=INT_MAX;

int sum(struct Node *node){
	int summary=0;
	while(node){
		summary+=node->cost;
		node=node->prev;
	}
	return summary;
}

int inme(struct Node *node,int who){
	int ok=0;
	while(node && !ok){
		if(node->id==who)
			ok=1;
		node=node->prev;
	}
	return ok;
}

void display_outcome(struct Node *node,int newmin){
	min=newmin;
	printf("%d",STARTNODE);
	while(node){
		printf("<===%d ",node->id);
		node=node->prev;
	}
	printf(".And cost=%d\n",min );
}

void branchbound(int (*map)[NODESIZE]){
	struct Node *currentnode=malloc(sizeof(struct Node));
	currentnode->id=STARTNODE,currentnode->height=0,currentnode->prev=NULL,currentnode->cost=0;
	push(currentnode);
	struct Node *node;
	struct Node *neibors[NODESIZE];
	int neiborsize,i;
	while(!empty()){
		currentnode=top();
		if(currentnode->height==NODESIZE-1 && currentnode->cost+map[currentnode->id][STARTNODE]<min)
			display_outcome(currentnode,currentnode->cost+map[currentnode->id][STARTNODE]);
		pop();
		if(currentnode->cost > min){
			printf("drop one.\n");
			continue;
		}
		neiborsize=0;
		for(i=0;i<NODESIZE;i++)
			if(i!=currentnode->id && !inme(currentnode,i)){
				node=malloc(sizeof(struct Node));
				node->id=i,node->height=currentnode->height+1,node->prev=currentnode;
				node->cost=currentnode->cost+map[currentnode->id][i];
				neibors[neiborsize++]=node;
			}
		insertsort(neibors,neiborsize);
		for(i=0;i<neiborsize;i++)
			push(neibors[i]);
	}
}

int main(int argc, char const *argv[])
{
	int map[NODESIZE][NODESIZE]={
		{INT_MAX,5,61,34,12},
		{57,INT_MAX,43,20,7},
		{39,42,INT_MAX,8,21},
		{6,50,42,INT_MAX,8},
		{41,26,10,35,INT_MAX}
	};
	branchbound(map);
	return 0;
}
