#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
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

//statusstack define
static int stack2[STACKSIZE];
static int sp2=-1;
static int empty2(void){
	return sp2==-1;
}
static void push2(int status){
	stack2[++sp2]=status;
}
static int pop2(void){
	return stack2[sp2--];
}
static int top2(void){
	return stack2[sp2];
}
static void change2(int newstatus){
	stack2[sp]=newstatus;
}
//statusstack define OK

void insert_btree(btlink *btree,int vertex){
	btlink cur=*btree,parent=NULL;
	btlink new=malloc(sizeof(struct BTree));
	new->vertex=vertex;
	new->left=new->right=NULL;
	if(!cur){
		*btree=new;
		return;
	}
	while(cur){
		parent=cur;
		if(cur->vertex>=vertex)
			cur=cur->left;
		else
			cur=cur->right;
	}
	if(parent->vertex>=vertex)
		parent->left=new;
	else
		parent->right=new;
}

btlink insert_btree_recursive(btlink cur,int vertex){
	if(!cur){
		btlink new=malloc(sizeof(struct BTree));
		new->vertex=vertex;
		new->left=new->right=NULL;
		return new;
	}
	if(vertex<=cur->vertex)
		cur->left=insert_btree_recursive(cur->left,vertex);
	else
		cur->right=insert_btree_recursive(cur->right,vertex);
	return cur;
}

btlink find_rightleftmostnode(btlink node){
	btlink cur=node->right;
	btlink parent=node;
	while(cur->left){
		parent=cur;
		cur=cur->left;
	}
	if(parent->vertex>=cur->vertex)
		parent->left=cur->right;
	else
		parent->right=cur->right;
	return cur;
}

void delete_btree(btlink *btree,int vertex){
	btlink cur=*btree,parent=NULL,target;
	if(!cur)
		return;
	while(cur && cur->vertex!=vertex){
		parent=cur;
		cur=(cur->vertex > vertex)?(cur->left):(cur->right);
	}
	target=cur;
	if(!target)
		return;
	if(target->right && target->left){
		btlink leftmost=find_rightleftmostnode(target);
		target->vertex=leftmost->vertex;
		target=leftmost;
	}else if(target->left){
		if(parent){
			if(parent->left==target)
				parent->left=target->left;
			else
				parent->right=target->left;
		}else
			*btree=target->left;
	}else if(target->right){
		if(parent){
			if(parent->left==target)
				parent->left=target->right;
			else
				parent->right=target->right;
		}else
			*btree=target->right;
	}else{
		if(parent){
			if(parent->left==target)
				parent->left=NULL;
			else
				parent->right=NULL;
		}else
			*btree=NULL;
	}
	free(target);
}

void prefix_recursive(btlink root){
	if(root){
		printf("%d ",root->vertex );
		prefix_recursive(root->left);
		prefix_recursive(root->right);
	}
}

void infix_recursive(btlink root){
	if(root){
		infix_recursive(root->left);
		printf("%d ",root->vertex );
		infix_recursive(root->right);
	}
}

void suffix_recursive(btlink root){
	if(root){
		suffix_recursive(root->left);
		suffix_recursive(root->right);
		printf("%d ",root->vertex );
	}
}

void prefix_nonrecursive(btlink btree){
	printf("prefix_nonrecursive:\n");
	btlink cur=btree;
	while(cur || !empty()){
		while(cur){
			printf("%d ",cur->vertex);
			push(cur);
			cur=cur->left;
		}
		if(!cur){
			cur=pop();
			cur=cur->right;
		}
	}
	printf("\n");
}

void infix_nonrecursive(btlink btree){
	printf("infix_nonrecursive:\n");
	btlink cur=btree;
	while(cur || !empty()){
		while(cur){
			push(cur);
			cur=cur->left;
		}
		if(!cur){
			cur=pop();
			printf("%d ",cur->vertex );
			cur=cur->right;
		}
	}
	printf("\n");
}

void suffix_nonrecursive(btlink btree){
	printf("suffix_nonrecursive:\n");
	btlink cur=btree;
	int status;
	push(cur);push2(0);
	while(!empty()){
		status=top2();
		switch(status){
			case 0:
				cur=top();
				change2(1);
				if(cur->left){
					push(cur->left);
					push2(0);
				}
				break;
			case 1:
				cur=top();
				change2(2);
				if(cur->right){
					push(cur->right);
					push2(0);
				}
				break;
			default:
				cur=pop();pop2();
				printf("%d ",cur->vertex);
		}
	}
	printf("\n");
}

void destroy_tree(btlink btree){
	if(btree){
		destroy_tree(btree->left);
		destroy_tree(btree->right);
		free(btree);
	}
}

btlink search_btree_recursive(btlink btree,int target){
	if(!btree || btree->vertex==target)
		return btree;
	if(btree->vertex>target)
		return search_btree_recursive(btree->left,target);
	else
		return search_btree_recursive(btree->right,target);
}

btlink search_btree_nonrecursive(btlink btree,int target){
	btlink cur=btree;
	btlink retval=NULL;
	while(cur){
		if(cur->vertex==target){
			retval=cur;
			break;
		}else
			cur=cur->vertex>target?cur->left:cur->right;
	}
	return retval;
}

int head,rear;
#define QUEUESIZE 100
btlink queue[QUEUESIZE];

int empty_queue(){
	return head==rear;
}

int full_queue(){
	return head=(rear+1)%QUEUESIZE;
}

void enqueue(btlink item){
	queue[rear]=item;
	rear=(rear+1)%QUEUESIZE;
}

btlink dequeue(){
	btlink retval=queue[head];
	head=(head+1)%QUEUESIZE;
	return retval;
}

void bfs(btlink tree){
	enqueue(tree);
	btlink cur;
	while(!empty_queue()){
		cur=dequeue();
		printf("%d ", cur->vertex);
		if(cur->left)
			enqueue(cur->left);
		if(cur->right)
			enqueue(cur->right);
	}
	printf("\n");
}

