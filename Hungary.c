#include <stdio.h>
#include <string.h>
#define ARRAYSIZE(array) (sizeof array/sizeof *array)
struct Node{
	int x;
	int y;
};

int available(struct Node *node1,struct Node *node2){
	return (node1->x>=node2->x && node1->y>=node2->y);
}

void showresult(int *match,struct Node *pset,int qsize,struct Node *qset){
	for(int i=0;i<qsize;i++)
		if(match[i]!=-1)
			printf("(%d,%d)=>(%d,%d)\n",
					pset[match[i]].x,pset[match[i]].y,
					qset[i].x,qset[i].y);
}
#define TRUE 1
#define FALSE 0
int findout(int *match,
		struct Node *pset,struct Node *qset,
		int qsize,int *used,int who,int head){
	int new;
	for(int j=head;j<qsize;j++)
		if(available(&pset[who],&qset[j])){
			used[j]=1;
			if(match[j]==-1 || 
			findout(match,pset,qset,qsize,used,match[j],j+1)){
				match[j]=who;
				return TRUE;
			}
		}
	return FALSE;
}

void hungary(struct Node *pset,int psize,struct Node *qset,int qsize){
	int counter=0,used[qsize],match[psize];
	memset(used,0,sizeof(int)*qsize);
	for(int i=0;i<qsize;i++)
		match[i]=-1;
	for(int i=0;i<psize;i++)
		if(findout(match,pset,qset,qsize,used,i,0))
			counter++;
	printf("counter=%d\n",counter);
	showresult(match,pset,qsize,qset);
}

int main(){
	struct Node pset[]={
		{5,2},{4,1},{5,2},{2,1},{2,3},{1,2},{5,3},{4,5},{2,6},{2,2}
	},qset[]={
		{3,5},{1,1},{5,3},{2,3},{2,4},{4,1},{3,1},{1,3},{3,2},{3,2}
	};
	int psize=ARRAYSIZE(pset),qsize=ARRAYSIZE(qset);
	hungary(pset,psize,qset,qsize);
} 
