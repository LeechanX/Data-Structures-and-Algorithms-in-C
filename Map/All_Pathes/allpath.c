#include <stdio.h>
#include "map.h"

#define EDGE 20

void display_answer(int *answer,int size){
	for(int i=0;i<size;i++)
		printf("=>%d",answer[i]);
	printf("\n");
}

void allpath(struct Graph *map,int *answer,int endnode,int step){
	//now handle step
	int prevnode=answer[step-1];
	if(prevnode==endnode)
		display_answer(answer,step);
	struct Node *cur=map->nodes[prevnode]->next;
	while(cur){
		answer[step]=cur->vertex;
		allpath(map,answer,endnode,step+1);
		cur=cur->next;
	}
}

int isneibor(struct Graph *map,int node,int neibor){
	struct Node *cur=map->nodes[node]->next;
	int retval=0;
	while(cur && !retval){
		if(cur->vertex==neibor)
			retval=1;
		cur=cur->next;
	}
	return retval;
}

void allpath_nor(struct Graph *map,int startnode,int endnode){
	int answer[EDGE];
	int record[EDGE];
	answer[0]=startnode;
	record[0]=startnode;
	int step=1,prevnode;
	record[step]=-1;
	while(step>=1){
		prevnode=answer[step-1];
		record[step]++;
		while(record[step]<map->nodesize && !isneibor(map,prevnode,record[step]))
			record[step]++;
		if(record[step]==map->nodesize)
			step--;
		else if(record[step]==endnode){
			answer[step]=record[step];
			display_answer(answer,step+1);
		}else{
			answer[step]=record[step];
			step+=1;
			record[step]=-1;
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc==1){
		printf("argv NULL!\n");
		return (1);
	}
	struct Graph *map=read_map(argv[1]);
	//display_debug(map);
	int startnode,endnode;
	int answer[EDGE];
	startnode=0,endnode=7;
	//recursive
	answer[0]=startnode;
	allpath(map,answer,endnode,1);
	printf("*************\n");
	//no recursive
	allpath_nor(map,startnode,endnode);
	return 0;
}