#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#define MAXSIZE 100
struct Set{
	int vertex;
	struct Set *parent;
};

extern int rank[];

struct Set **init_set(int size);
struct Set *find_set(struct Set *);
void union_set(struct Set *,struct Set *);

#endif