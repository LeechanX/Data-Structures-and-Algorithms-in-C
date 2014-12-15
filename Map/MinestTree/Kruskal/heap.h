#ifndef HEAP_H
#define HEAP_H

struct Heap{
	int size;
	struct Edge **data;
};

struct Edge{
	int node1;
	int node2;
	int weight;
};

struct Heap *init_heap(int size);
void heap_swap(struct Heap *heap,int pos1,int pos2);
void heap_hold(struct Heap *heap,int pos);
void heap_insert(struct Heap *heap,int node1,int node2,int weight);
struct Edge *delete_min(struct Heap *heap);

#endif