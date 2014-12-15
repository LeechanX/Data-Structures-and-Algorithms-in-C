#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

struct Set{
	int vertex;
	struct Set *parent;
};
typedef struct Set *slink;

struct Query{
	int test1;
	int test2;
	char ok;
};

void search(btlink btree,int target){
	btlink node=search_btree_recursive(btree,target);
	printf("use nonrecursive:\n");
	node=search_btree_nonrecursive(btree,target);
	if(!node){
		printf("No found!\n");
		return;
	}else
		printf("%d!\n",node->vertex );
	printf("use recursive:\n");
	node=search_btree_recursive(btree,target);
	if(!node){
		printf("No found!\n");
		return;
	}else
		printf("find %d.\n",node->vertex );
}

int find_set(slink *sets,int member){
	slink current=sets[member],parent=current->parent;
	while(current!=parent){
		current=parent;
		parent=current->parent;
	}
	return parent->vertex;
}

void union_set(slink *sets,int member1,int member2){
	int set1=find_set(sets,member1),set2=find_set(sets,member2);
	sets[set2]->parent=sets[set1];
}

void tartjan_dfs(btlink btree,int *visited,slink *sets,int (*query)[2]){
	if(!btree)
		return;
	tartjan_dfs(btree->left,visited,sets,query);
	if(btree->left){
		union_set(sets,btree->vertex,btree->left->vertex);
		sets[find_set(sets,btree->vertex)]->parent=sets[btree->vertex];
	}
	tartjan_dfs(btree->right,visited,sets,query);
	if(btree->right){
		union_set(sets,btree->vertex,btree->right->vertex);
		sets[find_set(sets,btree->vertex)]->parent=sets[btree->vertex];
	}
	visited[btree->vertex]=1;
	int query_obj;
	for(int i=0;i<8;i++){
		if(query[i][0]==btree->vertex && visited[query[i][1]])
			printf("%d,%d LCA=%d\n",btree->vertex,query[i][1],find_set(sets,query[i][1]));
		else if(query[i][1]==btree->vertex && visited[query[i][0]])
			printf("%d,%d LCA=%d\n",btree->vertex,query[i][0],find_set(sets,query[i][0]));
	}
}

int lca_binarysearchtree_only(btlink tree,int one,int other){
	btlink cur=tree;
	int retval=-1;
	if(one>other){
		int tmp=one;
		one=other;
		other=tmp;
	}
	while(cur && retval==-1){
		if(one<cur->vertex && other<cur->vertex)
			cur=cur->left;
		else if(one>cur->vertex && other>cur->vertex)
			cur=cur->right;
		else if(one<=cur->vertex && other>=cur->vertex)
			retval=cur->vertex;
	}
	return retval;
}

void method_only_binarysearchtree(btlink tree,int (*query)[2]){
	for(int i=0;i<8;i++)
		printf("%d,%d LCA=%d\n",query[i][0],query[i][1],lca_binarysearchtree_only(tree,query[i][0],query[i][1]));
}

int lca_fool(btlink tree,int one,int other){
	btlink cur=tree;
	int visited[20]={};
	while(cur){
		visited[cur->vertex]=1;
		if(cur->vertex<one)
			cur=cur->right;
		else if(cur->vertex>one)
			cur=cur->left;
		else
			break;
	}
	cur=tree;
	int retval=-1;
	while(cur){
		if(visited[cur->vertex])
			retval=cur->vertex;
		if(cur->vertex<other)
			cur=cur->right;
		else if(cur->vertex>other)
			cur=cur->left;
		else
			break;
	}
	return retval;
}


void method_fool(btlink tree,int (*query)[2]){
	for(int i=0;i<8;i++)
		printf("%d,%d LCA=%d\n",query[i][0],query[i][1],lca_fool(tree,query[i][0],query[i][1]));
}

int main(int argc, char const *argv[]){
	int data[]={8,1,19,4,2,7,6,3,16,18,12,11,14,5};
	int size=sizeof(data)/sizeof(int);
	btlink btree=NULL;
	int i=0;
	slink sets[20];
	int visited[20];
	while(i<size){
		sets[data[i]]=malloc(sizeof(struct Set));
		sets[data[i]]->vertex=data[i];
		sets[data[i]]->parent=sets[data[i]];
		visited[data[i]]=0;
		btree=insert_btree_recursive(btree,data[i++]);
	}
	int query[8][2]={{1,3},{2,5},{3,8},{11,14},{11,16},{14,18},{5,19},{4,14}};
	printf("cool way:\n");
	tartjan_dfs(btree,visited,sets,query);
	printf("only binarysearchtree:\n");
	method_only_binarysearchtree(btree,query);
	printf("fool:\n");
	method_fool(btree,query);
	return 0;
}