#include <stdio.h>
#include <stdlib.h>
#include "list.h"

llink find_item(llink list,int vertex){
	while(list){
		if(list->vertex==vertex)
			return list;
		list=list->next;
	}
	return NULL;
}

void delete_item_advanced(llink node){
	llink next=node->next;
	if(next){
		node->vertex=next->vertex;
		node->next=next->next;
		free(next);
	}else
		printf("cannot delete %d for its the last item\n",node->vertex);
}

int main(int argc, char const *argv[])
{
	int data[]={1,2,3,4,5,6,7};
	int size=sizeof(data)/sizeof(int);
	llink list=NULL;
	int i;
	for(i=0;i<size;i++)
		insert_list(&list,data[i]);
	display_list(list);
	int test[]={4,7,5,6,3,1,2};
	llink node;
	for(i=0;i<size;i++){
		node=find_item(list,test[i]);
		delete_item_advanced(node);
		display_list(list);
	}
	return 0;
}