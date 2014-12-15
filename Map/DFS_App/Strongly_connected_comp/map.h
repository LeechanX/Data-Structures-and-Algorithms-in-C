#ifndef MAP_H
#define MAP_H

struct Node{
	int vertex;
	struct Node *next;
};

struct Graph{
	struct Node **nodes;
	int nodesize;
	int sp;
};

struct Graph *graph_init(int);
void graph_insertnode(struct Graph *,int);
void graph_insertedge(struct Graph *,int,int);
void display_debug(struct Graph *);
struct Graph *read_map(char const *);

#endif