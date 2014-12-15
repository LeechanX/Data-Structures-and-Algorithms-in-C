#include <stdlib.h>
#include "disjointset.h"

int rank[MAXSIZE];

struct Set **init_set(int size){
	int i;
	struct Set **set=malloc(sizeof(struct Set *)*size);
	for(i=0;i<size;i++){
		set[i]=malloc(sizeof(struct Set));
		set[i]->vertex=i;
		set[i]->parent=set[i];
	}
	return set;
}

struct Set *find_set(struct Set *item){
	if(item->parent==item)
		return item;
	item->parent=find_set(item->parent);
	return item->parent;
}

void union_set(struct Set *one,struct Set *other){
	if(rank[one->vertex]<rank[other->vertex])
		one->parent=other;
	else{
		if(rank[one->vertex]==rank[other->vertex])
			rank[one->vertex]++;
		other->parent=one;
	}
}