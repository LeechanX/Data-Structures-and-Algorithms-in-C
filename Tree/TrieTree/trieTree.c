#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 23

struct Tnode{
	int value;
	struct Tnode *next[26];
};

typedef struct Tnode *tlink;

void init_pointer_array(tlink node){
	int i;
	for(i=0;i<26;i++)
		node->next[i]=NULL;
}

tlink create_tree(){
	tlink root=(tlink)malloc(sizeof(struct Tnode));
	if(!root)
		return NULL;
	root->value=-1;
	init_pointer_array(root);
	return root;
}

void insert_node(tlink root,char *name,int value){
	tlink now=root;
	tlink new;
	int sp=0;
	int size=strlen(name);
	while(sp<size){
		if(!(now->next[name[sp]-'a'])){
			new=(tlink)malloc(sizeof(struct Tnode));
			if(!new)
				return;
			new->value=-1;
			init_pointer_array(new);
			now->next[name[sp]-'a']=new;
		}
		now=now->next[name[sp]-'a'];
		sp++;
	}
	now->value=value;
}

void insert_node_r(tlink root,char *name,int step,int size,int value){
	if(step==size)
		return;
	char ch=name[step];
	tlink cur=root->next[ch-'a'];
	if(!cur){
		tlink new=(tlink)malloc(sizeof(struct Tnode));
		if(!new)
			return;
		root->next[ch-'a']=new;
		init_pointer_array(new);
		new->value=-1;
	}
	if(step==size-1)
		root->next[ch-'a']->value=value;
	insert_node_r(root->next[ch-'a'],name,step+1,size,value);
}

int search_tree(tlink root,char *name){
	int size=strlen(name);
	char ch;
	int retval=-1;
	tlink now=root;
	for(int i=0;i<size;i++){
		ch=name[i];
		now=now->next[ch-'a'];
		if(!now)
			return -1;
	}
	retval=now->value;
	return retval;
}

int search_tree_r(tlink root,char *name,int step,int size){
	if(step>size-1)
		return -1;
	char ch=name[step];
	tlink cur=root->next[ch-'a'];
	if(!cur)
		return -1;
	if(step==size-1)
		return cur->value;
	return search_tree_r(root->next[ch-'a'],name,step+1,size);
}

void destory_tree(tlink root){
	int i;
	if(!root)
		return;
	for(i=0;i<26;i++)
		destory_tree(root->next[i]);
	free(root);
}

int main(int argc, char const *argv[])
{
	char *string[]={
		"leechanx","lichenxuan","leechany","leechlian",
		"cong","congx","congxiaol","leechanxuan","liche",
		"zhangyumao","zhangyuzhou","zhanghongli","zhangweizhe",
		"zhai","alibaba","tencent","baidu","wangyi",
		"souhu","macos","windows","unix","linux",
	};
	int value[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
	tlink trietree=create_tree();
	for(int i=0;i<N;i++)
		//insert_node_r(trietree,string[i],0,strlen(string[i]),value[i]);
		insert_node(trietree,string[i],value[i]);
	for(int i=0;i<N;i++){
		int nr=search_tree(trietree,string[i]);
		int r=search_tree_r(trietree,string[i],0,strlen(string[i]));
		printf("%d=%d\n",nr,r);
	}
	printf("%d=%d\n", search_tree(trietree,"zhanghonglis"),search_tree_r(trietree,"zhanghonglis",0,strlen("zhanghonglis")));
	printf("%d=%d\n",search_tree(trietree,"zhanghongl"),search_tree_r(trietree,"zhanghongl",0,strlen("zhanghongl")));
	destory_tree(trietree);
	return 0;
}










