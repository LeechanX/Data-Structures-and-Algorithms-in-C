#ifndef TREECONVERT_H
#define TREECONVERT_H

struct Tree{
	char vertex;
	struct Tree *firstchild;
	struct Tree *nextsibling;
};

struct BinaryTree{
	char vertex;
	struct BinaryTree *left;
	struct BinaryTree *right;
};

typedef struct Tree *tlink;
typedef struct BinaryTree *btlink;

void prevfix(btlink);
void treeprevfix(tlink);
void forestprevfix(tlink *,int);

tlink binarytree2tree(btlink);
tlink *binarytree2forest(btlink,int *);

btlink treeconvert2btree(tlink);
btlink forestconvert2btree(tlink *,int);

#endif