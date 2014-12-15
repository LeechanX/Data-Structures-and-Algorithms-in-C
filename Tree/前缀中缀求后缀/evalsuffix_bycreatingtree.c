#include <stdio.h>
#include <stdlib.h>

struct BTree{
	int vertex;
	struct BTree *left;
	struct BTree *right;
};
typedef struct BTree *btlink;

int findposition_infix(int *seq,int head,int rear,int target){
	int i;
	for(i=rear-1;i>=0;i--)//一定要逆序查找，因为有权值相同的结点，如根节点=1，在中序里，这个1应该是是最后一个1
		if(seq[i]==target)
			return i;
	return -1;
}

btlink create_binarytree(int *prefix,int *infix,int prefixhead,
	int prefixrear,int infixhead,int infixrear){
	if(prefixrear-prefixhead<1)
		return NULL;
	btlink new=malloc(sizeof(struct BTree));
	int root_v=prefix[prefixhead];
	new->vertex=root_v;
	int root_position_infix=findposition_infix(infix,infixhead,infixrear,root_v);
	//int leftsubtree_size=root_position_infix-infixhead;
	int split_prefix=root_position_infix-infixhead+prefixhead+1;
	new->left=create_binarytree(prefix,infix,prefixhead+1,split_prefix,infixhead,root_position_infix);
	new->right=create_binarytree(prefix,infix,split_prefix,prefixrear,root_position_infix+1,infixrear);
	return new;
}

void suffix(btlink root){
	if(root){
		suffix(root->left);
		suffix(root->right);
		printf("%d ",root->vertex );
	}
}

int main(int argc, char const *argv[])
{
	int prefix[]={8,1,1,1,4,3,2,3,5,5,7,6,19,14,12,11,14,16,18};
	int infix[]={1,1,1,2,3,3,4,5,5,6,7,8,11,12,14,14,16,18,19};
	int size=sizeof(prefix)/sizeof(int);
	btlink btree=create_binarytree(prefix,infix,0,size,0,size);
	printf("suffix:\n");
	suffix(btree);
	printf("\n");
	return 0;
}