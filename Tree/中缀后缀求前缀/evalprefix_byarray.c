#include <stdio.h>
#include <stdlib.h>

int sp;

int findposition_infix(int *seq,int head,int rear,int target){
	int i;
	for(i=rear-1;i>=0;i--)//一定要逆序查找，因为有权值相同的结点，如根节点=1，在中序里，这个1应该是是最后一个1
		if(seq[i]==target)
			return i;
	return -1;
}

void create_prefix(int *infix,int *suffix,int infixhead,
	int infixrear,int suffixhead,int suffixrear,
	int *prefix){
	if(suffixrear-suffixhead<1)
		return;
	int root_v=suffix[suffixrear-1];
	prefix[sp++]=root_v;

	int root_position_infix=findposition_infix(infix,infixhead,infixrear,root_v);
	int split_suffix=root_position_infix-infixhead+suffixhead;

	//leftsubtree:
	create_prefix(infix,suffix,infixhead,root_position_infix,suffixhead,split_suffix,prefix);
	//rightsubtree:
	create_prefix(infix,suffix,root_position_infix+1,infixrear,split_suffix,suffixrear-1,prefix);
}

int main(int argc, char const *argv[])
{
	int infix[]={1,1,1,2,3,3,4,5,5,6,7,8,11,12,14,14,16,18,19};
	int suffix[]={1,1,3,2,3,5,6,7,5,4,1,11,14,12,18,16,14,19,8};
	int size=sizeof(suffix)/sizeof(int);
	int *prefix=malloc(sizeof(int)*size);
	create_prefix(infix,suffix,0,size,0,size,prefix);
	printf("prefix:\n");
	int i;
	for(i=0;i<size;i++)
		printf("%d ", prefix[i]);
	printf("\n");
	return 0;
}