#ifndef MAP_H
#define MAP_H

int **graph_init(int);
void graph_insertedge(int**,int,int,int);
void display_debug(int **,int);
int **read_map(char const *,int *);

#endif