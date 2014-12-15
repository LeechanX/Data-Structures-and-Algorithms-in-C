#include <stdio.h>
#include <stdlib.h>
#define LIMIT 20
#define BUCKETSIZE 10
#define MAP(x) (x/2)

struct List{
	int item;
	struct List *next;
};

struct Listhead{
	struct List *head;
};

int getvalue(int number,int pos){
	while(pos>1){
		number=number/10;
		pos--;
	}
	number%=10;
	return number;
}

void bucket_init(struct Listhead **buckets,int bucketsize){
	int i;
	for(i=0;i<bucketsize;i++){
		buckets[i]=malloc(sizeof(struct Listhead));
		buckets[i]->head=NULL;
	}
}

void list_add(struct Listhead **buckets,int item,int position){
	struct Listhead *list=buckets[position];
	struct List *new=malloc(sizeof(struct List));
	new->item=item;
	new->next=NULL;
	if(list->head){
		struct List *current=list->head,*prev=NULL;
		while(current){
			if(current->item>=item){
				new->next=current;
				if(prev){
					prev->next=new;
				}else{
					list->head=new;
				}
				break;
			}
			prev=current;
			current=current->next;
		}
		if(prev)
			prev->next=new;
	}else
		list->head=new;
}

void bucket_add(struct Listhead **buckets,int item,int pos){
	int newmap=getvalue(item,pos);
	list_add(buckets,item,MAP(newmap));
}

void bucket_scan(struct Listhead **buckets,int *data,int bucketsize){
	int sp=-1,i,nowvalue;
	struct List *list;
	for(i=0;i<bucketsize;i++){
		list=buckets[i]->head;
		while(list){
			nowvalue=list->item;
			data[++sp]=nowvalue;
			list=list->next;
		}
	}
}

void bucketsort(int *data,int size,int pos){
	struct Listhead *buckets[BUCKETSIZE];
	bucket_init(buckets,BUCKETSIZE);
	int i;
	for(i=0;i<size;i++)
		bucket_add(buckets,data[i],pos);
	bucket_scan(buckets,data,BUCKETSIZE);
}

void radix_sort(int *data,int size,int digitsize){
	int i;
	for(i=1;i<=digitsize;i++)
		bucketsort(data,size,i);
}

void displayoutcome(int *data,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", *(data+i));
	printf("\n");
}

int main(){
	/*
	*/
	int data[]={64,8,216,512,27,729,0,1,343,125,93};
	int size=sizeof(data)/sizeof(int);
	radix_sort(data,size,3);
	displayoutcome(data,size);
	return 0;
}