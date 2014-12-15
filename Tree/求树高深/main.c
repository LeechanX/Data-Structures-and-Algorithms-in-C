#include <stdio.h>
#include <stdlib.h>

struct Node{
	int vertex;
	int depth;
	struct Node *left;
	struct Node *right;
};

void insertnode(struct Node **treep,int vertex){
	struct Node *new=malloc(sizeof(struct Node));
	if(!new)
		exit(1);
	new->vertex=vertex;
	new->depth=0;
	new->left=new->right=NULL;
	if(!*treep){
		*treep=new;
		return ;
	}
	struct Node *tree=*treep,*parent=NULL;
	while(tree){
		parent=tree;
		tree=tree->vertex>=vertex?tree->left:tree->right;
		//稳定版本应该是tree=tree->vertex>vertex?tree->left:tree->right;
	}
	if(parent->vertex>=vertex)
		parent->left=new;
	else
		parent->right=new;
}

void prefix(struct Node *tree){
	if(tree){
		printf("%d ",tree->vertex);
		prefix(tree->left);
		prefix(tree->right);
	}
}

struct Node *stack[100];
int sp=-1;
void push(struct Node *item){
	stack[++sp]=item;
}
struct Node *pop(void){
	return stack[sp--];
}
int empty(void){
	return sp==-1;
}

int getdepth(struct Node *tree){
	struct Node *cur=tree;
	int curdepth=0,depth=0;
	while(cur || !empty()){
		while(cur){
			cur->depth=curdepth++;
			push(cur);
			if(cur->depth>depth)
				depth=cur->depth;
			cur=cur->left;
		}
		if(!cur){
			cur=pop();
			curdepth=cur->depth+1;
			cur=cur->right;
		}
	}
	return depth;
}

#define QSIZE 100
struct Node *queue[QSIZE];
int head,rear;
int qempty(void){
	return head==rear;
}
int qfull(void){
	return (rear+1)%QSIZE==head;
}
void enqueue(struct Node *item){
	if(qfull()){
		printf("Error:almost full.\n");
		return ;
	}
	queue[rear]=item;
	rear=(rear+1)%QSIZE;
}
struct Node *dequeue(void){
	if(qempty())
		return NULL;
	struct Node *ret=queue[head];
	head=(head+1)%QSIZE;
	return ret;
}

int getdepth_cuo(struct Node *tree){
	int depth=0;
	if(!tree)
		return depth;
	tree->depth=0;
	enqueue(tree);
	struct Node *cur;
	while(!qempty()){
		cur=dequeue();
		if(cur->depth>depth)
			depth=cur->depth;
		if(cur->left){
			cur->left->depth=cur->depth+1;
			enqueue(cur->left);
		}
		if(cur->right){
			cur->right->depth=cur->depth+1;
			enqueue(cur->right);
		}
	}
	return depth;
}

int main(int argc, char const *argv[])
{
	int data[]={7,10,2,8,4,8,6,1,9,11,3,5};
	int size=sizeof data/sizeof *data;
	struct Node *tree=NULL;
	for(int i=0;i<size;i++)
		insertnode(&tree,data[i]);
	int depth=getdepth(tree);
	printf("using prefix(dfs),height=depth=%d\n",depth);
	depth=getdepth_cuo(tree);
	printf("using bfs,height=depth=%d\n",depth);
	return 0;
}