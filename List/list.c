#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void insert_list(llink *list,int item){
	llink new=malloc(sizeof(struct List));
	if(!new)
		return;
	new->vertex=item;
	new->next=NULL;
	if(!*list){
		*list=new;
		return;
	}
	llink cur=*list;
	while(cur->next)
		cur=cur->next;
	cur->next=new;
}

void display_list(llink list){
	while(list){
		printf("%d ",list->vertex);
		list=list->next;
	}
	printf("\n");
}

llink insert_list_recursive(llink list,int item){
	if(!list){
		llink new=malloc(sizeof(struct List));
		if(!new)
			return new;
		new->vertex=item;
		new->next=NULL;
		return new;
	}
	list->next=insert_list_recursive(list->next,item);
	return list;
}

llink search_list(llink list,int item){
	llink retval=NULL;
	while(list && !retval){
		if(list->vertex==item)
			retval=list;
		list=list->next;
	}
	return retval;
}

int list_length(llink list){
	int length=0;
	while(list){
		length++;
		list=list->next;
	}
	return length;	
}