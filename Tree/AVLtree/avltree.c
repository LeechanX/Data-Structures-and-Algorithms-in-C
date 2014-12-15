#include <stdio.h>
#include <stdlib.h>

#define N 16

typedef struct AVLnode *tlink;
struct AVLnode{
	int vertex;
	tlink left;
	tlink right;
	int height;
};

int max(int a,int b){
	return a>b?a:b;
}

int height(tlink node){
	return node?node->height:-1;
}

tlink single_left_rotate(tlink k1){//RR
	tlink k2=k1->right;
	k1->right=k2->left;
	k2->left=k1;
	k1->height=max(height(k1->left),height(k1->right))+1;
	k2->height=max(height(k2->left),height(k2->right))+1;
	return k2;
}

tlink single_right_rotate(tlink k2){//LL
	tlink k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),height(k1->right))+1;
	return k1;
}

tlink double_rotate_right(tlink k1){//LR
	k1->left=single_left_rotate(k1->left);
	return single_right_rotate(k1);
}

tlink double_rotate_left(tlink k1){//RL
	k1->right=single_right_rotate(k1->right);
	return single_left_rotate(k1);
}

tlink insert_node(tlink tree,int vertex){
	tlink new=malloc(sizeof(struct AVLnode));
	if(!new)
		return new;
	new->vertex=vertex;
	new->height=0;
	new->left=new->right=NULL;
	if(!tree)
		return new;
	if(tree->vertex>=vertex){
		tree->left=insert_node(tree->left,vertex);
		if(height(tree->left)-height(tree->right)>1){//need to fix
			if(vertex<=tree->left->vertex)//l-l
				tree=single_right_rotate(tree);
			else//l-r
				tree=double_rotate_right(tree);
		}
	}else{
		tree->right=insert_node(tree->right,vertex);
		if(height(tree->right)-height(tree->left)>1){//need to fix
			if(vertex>tree->right->vertex)//r-r
				tree=single_left_rotate(tree);
			else//r-l
				tree=double_rotate_left(tree);
		}
	}
	tree->height=max(height(tree->left),height(tree->right))+1;
	return tree;
}

void infix(tlink root){
	if(root){
		infix(root->left);
		printf("%d(%d) ",root->vertex,root->height);
		infix(root->right);
	}
}

int main(int argc, char const *argv[])
{
	int data[N]={3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
	tlink tree=NULL;
	int i;
	for(i=0;i<N;i++)
		tree=insert_node(tree,data[i]);
	infix(tree);
	printf("\n");
	return 0;
}