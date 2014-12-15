#include <stdio.h>
#include "list.h"

int if_has_ring(llink list){
	llink cur_one=list,cur_two=list;
	int retval=0;
	while(cur_two){
		cur_one=cur_one->next;
		cur_two=cur_two->next;
		if(cur_two)
			cur_two=cur_two->next;
		if(cur_one==cur_two){
			retval=1;
			break;
		}
	}
	return retval;
}

void make_ring(llink list,llink that){
	llink cur=list;
	if(!cur)
		return;
	while(cur->next)
		cur=cur->next;
	cur->next=that;
}

llink find_item(llink list,int vertex){
	llink cur=list;
	while(cur){
		if(cur->vertex==vertex)
			return cur;
		cur=cur->next;
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	int data[]={1,2,3,4,5,6,7};
	int size=sizeof(data)/sizeof(int);
	llink list=NULL;
	int i;
	for(i=0;i<size;i++)
		insert_list(&list,data[i]);
	if(if_has_ring(list)){
		printf("Has ring!\n");
	}else{
		printf("No ring.\n");
	}
	make_ring(list,find_item(list,1));
	if(if_has_ring(list)){
		printf("Has ring!\n");
	}else{
		printf("No ring.\n");
	}
	return 0;
}