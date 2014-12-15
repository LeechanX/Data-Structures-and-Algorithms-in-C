#include <stdio.h>
#include <stdlib.h>

struct BTree{
	int vertex;
	struct BTree *left;
	struct BTree *right;
};
typedef struct BTree *btlink;

int findposition_infix(int *infix,int head,int rear,int target){
	int i;
	for(i=rear-1;i>=0;i--)//一定要逆序查找，因为有权值相同的结点，如根节点=1，在中序里，这个1应该是是最后一个1
		if(infix[i]==target)
			return i;
	return -1;
}

btlink create_binarytree(int *infix,int *suffix,
	int infixhead,int infixrear,int suffixhead,int suffixrear){
	if(infixrear-infixhead<1)
		return NULL;
	btlink new=malloc(sizeof(struct BTree));
	int root_v=suffix[suffixrear-1];
	new->vertex=root_v;
	int root_position_infix=findposition_infix(infix,infixhead,infixrear,root_v);

	int split_suffix=suffixhead+root_position_infix-infixhead;

	new->left=create_binarytree(infix,suffix,infixhead,root_position_infix,suffixhead,split_suffix);
	new->right=create_binarytree(infix,suffix,root_position_infix+1,infixrear,split_suffix,suffixrear-1);
	return new;
}

void prefix(btlink root){
	if(root){
		printf("%d ",root->vertex );
		prefix(root->left);
		prefix(root->right);
	}
}

int main(int argc, char const *argv[])
{
	int infix[]={1,1,1,2,3,3,4,5,5,6,7,8,11,12,14,14,16,18,19};
	int suffix[]={1,1,3,2,3,5,6,7,5,4,1,11,14,12,18,16,14,19,8};
	int size=sizeof(suffix)/sizeof(int);
	btlink btree=create_binarytree(infix,suffix,0,size,0,size);
	printf("prefix:\n");
	prefix(btree);
	printf("\n");
	return 0;
}