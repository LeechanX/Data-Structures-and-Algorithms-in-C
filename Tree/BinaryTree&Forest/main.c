#include <stdio.h>
#include <stdlib.h>
#include "treeconvert.h"

int main(){
	tlink tree=(tlink)malloc(sizeof(struct Tree));
	tree->vertex='A';
	tree->nextsibling=NULL;
	tlink nodeb=(tlink)malloc(sizeof(struct Tree));
	nodeb->vertex='B';
	nodeb->firstchild=NULL;
	tlink nodec=(tlink)malloc(sizeof(struct Tree));
	nodec->vertex='C';
	nodec->firstchild=NULL;
	tlink noded=(tlink)malloc(sizeof(struct Tree));
	noded->vertex='D';
	noded->nextsibling=NULL;
	noded->firstchild=NULL;
	tree->firstchild=nodeb;
	nodeb->nextsibling=nodec;
	nodec->nextsibling=noded;

	tlink tree2=(tlink)malloc(sizeof(struct Tree));
	tree2->vertex='E';
	tree2->nextsibling=NULL;
	tlink nodef=(tlink)malloc(sizeof(struct Tree));
	nodef->vertex='F';
	nodef->firstchild=NULL;
	nodef->nextsibling=NULL;
	tree2->firstchild=nodef;

	tlink tree3=(tlink)malloc(sizeof(struct Tree));
	tree3->vertex='G';
	tree3->nextsibling=NULL;
	tlink nodeh=(tlink)malloc(sizeof(struct Tree));
	nodeh->firstchild=NULL;
	tlink nodei=(tlink)malloc(sizeof(struct Tree));
	nodei->nextsibling=NULL;
	nodeh->nextsibling=nodei;
	tlink nodej=(tlink)malloc(sizeof(struct Tree));
	nodej->firstchild=nodej->nextsibling=NULL;
	nodei->firstchild=nodej;
	tree3->firstchild=nodeh;
	nodeh->vertex='H';
	nodei->vertex='I';
	nodej->vertex='J';

	tlink forest[3]={tree,tree2,tree3};
	printf("forest to binarytree:\n");
	btlink btree=forestconvert2btree(forest,3);
	prevfix(btree);
	printf("\n");
	printf("binarytree to forest:\n");
	int forestsize;
	tlink *rforest=binarytree2forest(btree,&forestsize);
	forestprevfix(rforest,forestsize);
	return 0;
}