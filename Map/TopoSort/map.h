#ifndef MAP_H
#define MAP_H

using namespace std;

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
struct Node *graph_getnode(struct Graph *,int);
void graph_insertedge(struct Graph *,int,int);
void display_debug(struct Graph *);
struct Graph *read_map(char const *,map <int,string> *);

#endif