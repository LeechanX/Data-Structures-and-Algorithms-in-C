#include <stdio.h>

int set_find(int *parent,int k){
	int parentnode=parent[k-1];
	if(parentnode==k)//is root
		return k;
	parent[k-1]=set_find(parent,parentnode);
	return parent[k-1];
}

void set_union(int *parent,int *rank,int i,int j){
	if(rank[i-1]<rank[j-1]){
		parent[j-1]=parent[i-1];
	}else{
		if(rank[i-1]==rank[j-1])
			rank[j-1]--;
		parent[i-1]=parent[j-1];
	}
}

int main(int argc, char const *argv[])
{
	int set[]={1,2,3,4,5,6,7,8,9,10};
	int size=sizeof(set)/sizeof(int);
	int k;
	int rank[10]={};
	int parent[10];
	for(k=0;k<size;k++)
		parent[k]=set[k];
	int i,j,parent_i,parent_j;
	while(scanf("%d%d",&i,&j)==2){
		parent_i=set_find(parent,i);
		parent_j=set_find(parent,j);
		if(parent_i==parent_j){
			printf("Already in same set.\n");
		}else{
			printf("Now union set.\n");
			set_union(parent,rank,parent_i,parent_j);
		}
	}
	return 0;
}