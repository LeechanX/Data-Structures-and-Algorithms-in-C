#include <stdio.h>

int findj(int *set,int size){
	int i;
	for(i=size-2;i>=0;i--)
		if(*(set+i)<*(set+i+1))
			break;
	return i;
}

int minestmax_inright(int *set,int j,int size){
	int i;
	for(i=size-1;i>j;i--)
		if(set[i]>set[j])
			break;
	return i;
}

void reverse(int *set,int head,int size){
	int copy[10],sp=-1;
	int i;
	for(i=head;i<size;i++)
		copy[++sp]=set[i];
	for(i=head;i<size;i++)
		set[i]=copy[sp--];
}

void displayarray(int *set,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", set[i]);
	printf("\n");
}

void full_array(int *set,int size){
	int j,k,tmp;
	displayarray(set,size);
	while((j=findj(set,size))!=-1){
		k=minestmax_inright(set,j,size);
		tmp=set[j];
		set[j]=set[k];
		set[k]=tmp;
		reverse(set,j+1,size);
		displayarray(set,size);
	}
}

int main()
{
	int set[]={1,2,3,4,5,6};
	int size=sizeof(set)/sizeof(int);
	full_array(set,size);
	return 0;
}