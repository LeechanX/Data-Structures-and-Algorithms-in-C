#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "map.h"
#define SOURCENODE 0

struct HeapNode{
	int vertex;
	int distance;
	int prev;
};

struct Heap{
	int size;
	struct HeapNode *data;
};

struct Heap *create_heap(struct Graph *map,int *distance){
	struct Heap *heap=malloc(sizeof(struct Heap));
	if(!heap)
		return heap;
	heap->size=map->nodesize;
	heap->data=malloc(sizeof(struct HeapNode)*map->nodesize);
	for(int i=0;i<map->nodesize;i++){
		heap->data[i].vertex=i;
		heap->data[i].distance=distance[i];
		heap->data[i].prev=-1;
	}
	return heap;
}

void swap_heap(struct Heap *heap,int pos1,int pos2){
	struct HeapNode tmp=heap->data[pos1];
	heap->data[pos1]=heap->data[pos2];
	heap->data[pos2]=tmp;
}

void hold_heap(struct Heap *heap,int pos){
	int left=2*pos+1,right=2*pos+2;
	int minpos=pos;
	if(left<heap->size && heap->data[left].distance<heap->data[minpos].distance)
		minpos=left;
	if(right<heap->size && heap->data[right].distance<heap->data[minpos].distance)
		minpos=right;
	if(minpos!=pos){
		swap_heap(heap,minpos,pos);
		hold_heap(heap,minpos);
	}
}

int empty_heap(struct Heap *heap){
	return heap->size==0;
}

struct HeapNode delete_heap(struct Heap *heap){
	struct HeapNode retval=heap->data[0];
	//heap->data[0]=heap->data[heap->size-1];
	swap_heap(heap,0,heap->size-1);
	heap->size--;
	hold_heap(heap,0);
	return retval;
}

void build_heap(struct Heap *heap){
	int lastparent=(heap->size-1)/2;
	for(int i=lastparent;i>=0;i--)
		hold_heap(heap,i);
}

void decrease_heap(struct Heap *heap,int vertex,int newdistance,int newprev){
	int pos=-1;
	for(int i=0;i<heap->size;i++)
		if(heap->data[i].vertex==vertex){
			pos=i;
			break;
		}
	if(pos==-1 || newdistance>=heap->data[pos].distance)
		return ;
	heap->data[pos].distance=newdistance;
	heap->data[pos].prev=newprev;
	int current=pos,parent=(current-1)/2;
	while(parent>=0){
		if(heap->data[parent].distance<=heap->data[current].distance)
			break;
		swap_heap(heap,parent,current);
		current=parent;
		parent=(current-1)/2;
	}
}

void prim(struct Graph *map){
	int distance[map->nodesize];
	for(int i=0;i<map->nodesize;i++)
		distance[i]=INT_MAX;
	distance[SOURCENODE]=0;
	struct Heap *heap=create_heap(map,distance);
	build_heap(heap);
	struct HeapNode node;
	struct Node *cur;
	while(!empty_heap(heap)){
		node=delete_heap(heap);
		cur=map->nodes[node.vertex]->next;
		while(cur){
			decrease_heap(heap,cur->vertex,cur->weight,node.vertex);
			cur=cur->next;
		}
	}
	//now print minest tree
	for(int i=0;i<map->nodesize;i++)
		printf("%d,distance=%d,prev=%d\n",heap->data[i].vertex,heap->data[i].distance,heap->data[i].prev);
}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	FILE *map_file=fopen(argv[1],"r");
	int directed,nodesize,edgesize;
	fscanf(map_file,"%d %d %d\n",&directed,&nodesize,&edgesize);
	struct Graph *map=graph_init(nodesize);

	char buff[1024];
	char *node_line=fgets(buff,sizeof(buff),map_file);
	char *node=strtok(node_line," \n");
	while(node){
		graph_insertnode(map,atoi(node));
		node=strtok(NULL," \n");
	}
	char *edge_line;
	int node1,node2,weight;
	while((edge_line=fgets(buff,sizeof(buff),map_file))){
		node=strtok(edge_line,"\t\n");
		node1=atoi(node);
		node=strtok(NULL,"\t\n");
		node2=atoi(node);
		node=strtok(NULL,"\t\n");
		weight=atoi(node);
		graph_insertedge(map,node1,node2,weight);
		if(!directed)
			graph_insertedge(map,node2,node1,weight);
	}
	fflush(map_file);
	fclose(map_file);

	display_debug(map);

	prim(map);

	return 0;
}