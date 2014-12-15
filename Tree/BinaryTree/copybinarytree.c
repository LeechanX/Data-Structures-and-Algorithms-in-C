#include <stdlib.h>
#include "binarytree.h"
#include "copybinarytree.h"
//nodestack define
static btlink stack[STACKSIZE];
static int sp=-1;
static int empty(void){
	return sp==-1;
}
static void push(btlink item){
	stack[++sp]=item;
}
static btlink pop(void){
	return stack[sp--];
}
static btlink top(void){
	return stack[sp];
}
//nodestack define OK

btlink copy_btree_recursive(btlink btree){
	if(!btree)
		return NULL;
	btlink root=malloc(sizeof(struct BTree));
	if(!root)
		exit(1);
	root->vertex=btree->vertex;
	root->left=copy_btree_recursive(btree->left);
	root->right=copy_btree_recursive(btree->right);
	return root;	
}

btlink copy_btree_nonrecursive(btlink btree){
	btlink cur=btree;
	btlink newbtree,newnode,parent=NULL;
	while(cur || !empty()){
		while(cur){
			newnode=malloc(sizeof(struct BTree));
			newnode->vertex=cur->vertex;
			newnode->left=newnode->right=NULL;
			push(parent);push(newnode);push(cur);
			parent=newnode;
			cur=cur->left;
		}
		if(!cur){
			cur=pop();
			newnode=pop();
			parent=pop();
			if(parent){
				if(parent->vertex>=newnode->vertex)
					parent->left=newnode;
				else
					parent->right=newnode;
			}else{
				newbtree=newnode;
			}
			parent=newnode;
			cur=cur->right;
		}
	}
	return newbtree;
}