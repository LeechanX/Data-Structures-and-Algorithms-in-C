#include <stdio.h>

//int hibbard[]={1,3,7,15,31};
int hibbard[]={1,3,5};

void displayoutcome(int *data,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ", *(data+i));
	printf("\n");
}

void shellsort(int *data,int size){
	int step,stepsp=sizeof(hibbard)/sizeof(int)-1;
	int i,j,tmp;
	while(stepsp>=0){
		step=hibbard[stepsp--];
		for(i=step;i<size;i++){
			tmp=data[i];
			for(j=i;j>=step && data[j-step]>tmp;j-=step)
				data[j]=data[j-step];
			data[j]=tmp;
		}
		displayoutcome(data,size);
	}
}

int main(){
	/*
	时间复杂度:O(n^2)
	空间复杂度:O(1)
	思路:对于每个位置，找到最小元素；一次循环后对应位置的数一定是当前最小的。
	*/
	int data[]={81,94,11,96,12,35,17,95,28,58,41,75,15};
	int size=sizeof(data)/sizeof(int);
	shellsort(data,size);
	displayoutcome(data,size);
	return 0;
}