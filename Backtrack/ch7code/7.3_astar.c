#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODESIZE 13
#define SOURCE 0
#define DEST 12
#define QSIZE 100

struct Node{
	int id;
	int vertex;
	struct Node *next;
};

struct TNode{
	int g;
	int f;
	int id;
	struct TNode *prev;
};

#define HEAPSIZE 100
struct Heap{
	int size;
	int capacity;
	struct TNode **data;
};
int heap_empty(struct Heap *heap){
	return heap->size==0;
}
void heap_swap(struct Heap *heap,int pos1,int pos2){
	struct TNode *tmp=heap->data[pos1];
	heap->data[pos1]=heap->data[pos2];
	heap->data[pos2]=tmp;
}
void heap_hold(struct Heap *heap,int pos){
	int left=2*pos+1,right=2*pos+2;
	int minpos=pos;
	if(right<heap->size && heap->data[right]->f < heap->data[minpos]->f)
		minpos=right;
	if(left<heap->size &&  heap->data[left]->f < heap->data[minpos]->f)
		minpos=left;
	if(minpos!=pos){
		heap_swap(heap,minpos,pos);
		heap_hold(heap,minpos);
	}
}
struct Heap *init_heap(void){
	struct Heap *heap=malloc(sizeof(struct Heap));
	heap->size=0,heap->capacity=HEAPSIZE;
	heap->data=malloc(sizeof(struct TNode*)*heap->capacity);
	return heap;
}

void insert_heap(struct Heap *heap,struct TNode *new){
	int currentpos=heap->size,parent;
	heap->data[heap->size++]=new;
	while((parent=(currentpos-1)/2)>=0){
		if(heap->data[currentpos]->f >= heap->data[parent]->f)
			break;
		heap_swap(heap,currentpos,parent);
	}
}

struct TNode *delete_min(struct Heap *heap){
	if(heap_empty(heap))
		return NULL;
	struct TNode *retval=heap->data[0];
	heap->data[0]=heap->data[--(heap->size)];
	heap_hold(heap,0);
	return retval;
}

void insertsort(struct TNode **data,int size){
	struct TNode *pivot;
	int i,j;
	for(i=1;i<size;i++){
		pivot=data[i];
		for(j=i-1;j>=0 && data[j]->f > pivot->f;j--)
			data[j+1]=data[j];
		data[j+1]=pivot;
	}
}

void insertedge(struct Node **map,int node1,int node2,int vertex){
	struct Node *cur=map[node1];
	struct Node *new=malloc(sizeof(struct Node));
	new->id=node2,new->vertex=vertex,new->next=cur;
	map[node1]=new;
}

int find_min_h(struct Node **map,int nodeid){
	struct Node *cur=map[nodeid];
	int h=INT_MAX;
	while(cur){
		if(cur->vertex < h)
			h=cur->vertex;
		cur=cur->next;
	}
	if(h==INT_MAX)
		h=0;
	return h;
}

void displayoutcome(struct TNode *node){
	printf("cost=%d\n",node->g );
	while(node){
		printf("%d <-",node->id );
		node=node->prev;
	}
	printf("\n");
}

void astar(struct Node **map){
	struct Heap *heap=init_heap();
	struct TNode *currentnode=malloc(sizeof(struct TNode));
	currentnode->id=SOURCE,currentnode->g=0,currentnode->prev=NULL,currentnode->f=0;
	insert_heap(heap,currentnode);
	struct Node *neibor;
	int i,htable[NODESIZE];
	struct TNode *node;
	for(i=0;i<NODESIZE;i++)
		htable[i]=find_min_h(map,i);
	while(!heap_empty(heap)){
		currentnode=delete_min(heap);
		if(currentnode->id==DEST){
			displayoutcome(currentnode);
			break;
		}
		neibor=map[currentnode->id];
		while(neibor){
			node=malloc(sizeof(struct TNode));
			node->id=neibor->id;
			node->g=currentnode->g+neibor->vertex;
			node->f=node->g+htable[node->id];
			node->prev=currentnode;
			insert_heap(heap,node);
			neibor=neibor->next;
		}
	}
}

int main(int argc, char const *argv[]){
	struct Node *map[NODESIZE]={};
	insertedge(map,SOURCE,1,2);
	insertedge(map,SOURCE,2,5);
	insertedge(map,SOURCE,3,1);
	insertedge(map,SOURCE,4,6);
	insertedge(map,1,5,1);
	insertedge(map,1,5,4);
	insertedge(map,2,5,9);
	insertedge(map,2,7,7);
	insertedge(map,3,5,3);
	insertedge(map,3,7,4);
	insertedge(map,4,6,7);
	insertedge(map,4,7,4);
	insertedge(map,5,8,6);
	insertedge(map,5,10,7);
	insertedge(map,6,8,4);
	insertedge(map,6,9,3);
	insertedge(map,6,11,5);
	insertedge(map,7,9,1);
	insertedge(map,7,10,4);
	insertedge(map,7,11,5);
	insertedge(map,8,DEST,3);
	insertedge(map,9,DEST,1);
	insertedge(map,10,DEST,2);
	insertedge(map,11,DEST,5);
	astar(map);
	return 0;
}