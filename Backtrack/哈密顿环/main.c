#include <stdio.h>

#define STARTNODE 0

int isneibor(int (*map)[6],int node1,int node2){
	return map[node1][node2];
}

void displayoutcome(int *answer,int size){
	for(int i=0;i<size;i++)
		printf("%d ",*(answer+i) );
	printf("\n");
}

int available(int *answer,int step,int sel){
	int ok=1;
	for(int i=0;i<step && ok;i++)
		if(*(answer+i)==sel)
			ok=0;
	return ok;
}

void backtrace_recursive(int (*map)[6],int nodesize,int *answer,int step){
	if(step==nodesize && isneibor(map,answer[step-1],STARTNODE)){
		displayoutcome(answer,step);
		return ;	
	}
	int curnode=answer[step-1];
	for(int sel=0;sel<nodesize;sel++)
		if(map[curnode][sel] && available(answer,step,sel)){
			answer[step]=sel;
			backtrace_recursive(map,nodesize,answer,step+1);
		}
}

void backtrace_nonrecursive(int (*map)[6],int nodesize){
	int answer[nodesize],record[nodesize],step=1,curnode;
	record[0]=STARTNODE;
	record[step]=-1;
	while(step>=1){
		record[step]++;
		curnode=answer[step-1];
		while(record[step]<nodesize && !(map[curnode][record[step]] && available(answer,step,record[step])))
			record[step]++;
		if(record[step]==nodesize)
			step--;
		else{
			answer[step]=record[step];
			if(step==nodesize-1 && isneibor(map,answer[step],STARTNODE))
				displayoutcome(answer,step+1);
			else{
				step++;
				record[step]=-1;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int map[6][6]={
        {0,1,0,1,1,1,},
        {1,0,1,0,1,0,},
        {0,1,0,1,0,0,},
        {1,0,1,0,1,1,},
        {1,1,0,1,0,0,},
        {1,0,0,1,0,0,}
    };
    int nodesize=6;
    
    int answer[6];
    answer[0]=STARTNODE;
    backtrace_recursive(map,nodesize,answer,1);
    /*
    backtrace_nonrecursive(map,nodesize);
    */
	return 0;
}