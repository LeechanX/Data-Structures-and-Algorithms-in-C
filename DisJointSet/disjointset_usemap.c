#include <stdio.h>
#include <stdlib.h>

struct SetNode{
	int vertex;
	int rank;
	struct SetNode *parent;
};
typedef struct SetNode *snlink;

snlink create_set(int vertex){
	snlink node=malloc(sizeof(struct SetNode));
	if(!node)
		return node;
	node->vertex=vertex;
	node->rank=0;
	node->parent=node;
	return node;
}

snlink find_set(snlink node){
	if(node==node->parent)
		return node->parent;
	node->parent=find_set(node->parent);
	return node->parent;
}

void union_set(snlink node1,snlink node2){
	printf("Union now.\n");
	if(node1->rank<node2->rank)
		node1->parent=node2;
	else{
		if(node1->rank==node2->rank)
			node1->rank++;
		node2->parent=node1;
	}
}

int main(int argc, char const *argv[])
{
	int set[]={1,2,3,4,5,6,7,8,9,10};
	int size=sizeof(set)/sizeof(int);
	int i;
	snlink disjointset[size];
	for(i=0;i<size;i++)
		disjointset[i]=create_set(i);
	int j;
	snlink set1,set2;
	while(scanf("%d%d",&i,&j)==2){
		set1=find_set(disjointset[i-1]),set2=find_set(disjointset[j-1]);
		if(set1==set2)
			printf("Already in same set.\n");
		else
			union_set(set1,set2);
	}
	return 0;
}