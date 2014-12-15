#include <stdio.h>
#include <stdlib.h>
#include "treeconvert.h"

void prevfix(btlink root){
	if(root){
		printf("%c ", root->vertex);
		prevfix(root->left);
		prevfix(root->right);
	}
}
void treeprevfix(tlink root){
	if(root){
		printf("%c ", root->vertex);
		treeprevfix(root->firstchild);
		treeprevfix(root->nextsibling);
	}
}

void forestprevfix(tlink *forest,int size){
	int i;
	for(i=0;i<size;i++){
		printf("tree %d:", i+1);
		treeprevfix(forest[i]);
		printf("\n");
	}
}

tlink binarytree2tree(btlink btree){
	//only when binarytree root has no right child
	if(!btree)
		return NULL;
	tlink tree=malloc(sizeof(struct Tree));
	tree->vertex=btree->vertex;
	tree->firstchild=binarytree2tree(btree->left);
	tree->nextsibling=binarytree2tree(btree->right);
	return tree;
}

tlink *binarytree2forest(btlink tree,int *newforestsize){
	int sp=0;
	tlink *forest=malloc(sizeof(tlink)*10);
	btlink current=tree,rmright;
	while(current){
		rmright=current;
		current=current->right;
		rmright->right=NULL;
		forest[sp++]=binarytree2tree(rmright);
	}
	*newforestsize=sp;
	return forest;
}

btlink treeconvert2btree(tlink tree){
	if(!tree)
		return NULL;
	btlink newbtreenode=malloc(sizeof(struct BinaryTree));
	newbtreenode->vertex=tree->vertex;
	newbtreenode->left=treeconvert2btree(tree->firstchild);
	newbtreenode->right=treeconvert2btree(tree->nextsibling);
	return newbtreenode;
}

btlink forestconvert2btree(tlink *forest,int forestsize){
	if(!forest)
		return NULL;
	int i;
	btlink btree=treeconvert2btree(forest[0]);
	btlink prevsubbtree=btree;
	for(i=1;i<forestsize;i++){
		prevsubbtree->right=treeconvert2btree(forest[i]);
		prevsubbtree=prevsubbtree->right;
	}
	return btree;
}

