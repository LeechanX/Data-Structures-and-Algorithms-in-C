#include <stdio.h>
#include "binarytree.h"
#include "copybinarytree.h"
#include "reverseisotree.h"

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

int main(int argc, char const *argv[]){
	int data[]={8,1,19,4,3,2,5,7,6,14,3,1,16,18,12,11,14,1,5};
	int size=sizeof(data)/sizeof(int);
	btlink btree=NULL;
	int i=0;
	while(i<size)
		//insert_btree(&btree,data[i++]);
		btree=insert_btree_recursive(btree,data[i++]);
	infix_recursive(btree);printf("\n");

	for(i=size-1;i>=0;i--){
		delete_btree(&btree,data[i]);
		infix_recursive(btree);printf("\n");
	}
	/*
	printf("====Traversal=======\n");
	printf("prefix:\n");
	prefix_recursive(btree);
	printf("\n");
	printf("infix:\n");
	infix_recursive(btree);
	printf("\n");
	printf("suffix:\n");
	suffix_recursive(btree);
	printf("\n");
	printf("layerfix:\n");
	bfs(btree);
	
	printf("=====Search======\n");
	search(btree,5);
	search(btree,16);
	search(btree,20);
	
	printf("=====CopyTree======\n");
	printf("use recursive:\n");
	btlink newbtree=copy_btree_recursive(btree);
	prefix_nonrecursive(newbtree);
	infix_nonrecursive(newbtree);
	suffix_nonrecursive(newbtree);
	printf("use nonrecursive:\n");
	btlink newbtree2=copy_btree_nonrecursive(btree);
	prefix_nonrecursive(newbtree2);
	infix_nonrecursive(newbtree2);
	suffix_nonrecursive(newbtree2);

	printf("=====Delete======\n");
	delete_btree(&btree,6);
	infix_nonrecursive(btree);
	delete_btree(&btree,19);
	infix_nonrecursive(btree);
	delete_btree(&btree,4);
	infix_nonrecursive(btree);
	delete_btree(&btree,8);
	infix_nonrecursive(btree);

	printf("=====DestroyTree======\n");
	destroy_tree(btree);
	destroy_tree(newbtree);
	destroy_tree(newbtree2);
	*/
	/*
	btree=reverse_btree_iso(btree);
	printf("====Traversal=======\n");
	printf("prefix:\n");
	prefix_recursive(btree);
	printf("\n");
	printf("infix:\n");
	infix_recursive(btree);
	printf("\n");
	printf("suffix:\n");
	suffix_recursive(btree);
	printf("\n");
	prefix_nonrecursive(btree);
	infix_nonrecursive(btree);
	suffix_nonrecursive(btree);

	printf("layerfix:\n");
	bfs(btree);
	*/
	return 0;
}