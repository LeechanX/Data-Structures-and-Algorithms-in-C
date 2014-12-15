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

void create_suffix(int *prefix,int *infix,int prefixhead,
	int prefixrear,int infixhead,int infixrear,
	int *suffix){
	if(prefixrear-prefixhead<1)
		return;
	int root_v=prefix[prefixhead];
	suffix[sp--]=root_v;

	int root_position_infix=findposition_infix(infix,infixhead,infixrear,root_v);
	int split_prefix=root_position_infix-infixhead+prefixhead+1;

	//rightsubtree:
	create_suffix(prefix,infix,split_prefix,prefixrear,root_position_infix+1,infixrear,suffix);
	//leftsubtree:
	create_suffix(prefix,infix,prefixhead+1,split_prefix,infixhead,root_position_infix,suffix);
}

int main(int argc, char const *argv[])
{
	int prefix[]={8,1,1,1,4,3,2,3,5,5,7,6,19,14,12,11,14,16,18};
	int infix[]={1,1,1,2,3,3,4,5,5,6,7,8,11,12,14,14,16,18,19};
	int size=sizeof(prefix)/sizeof(int);
	int *suffix=malloc(sizeof(int)*size);
	sp=size-1;
	create_suffix(prefix,infix,0,size,0,size,suffix);
	printf("suffix:\n");
	int i;
	for(i=0;i<size;i++)
		printf("%d ", suffix[i]);
	printf("\n");
	return 0;
}