#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>

using namespace std;

int **init_map(int nodesize){
	int **graph=(int **)malloc(sizeof(int *)*nodesize);
	for(int i=0;i<nodesize;i++){
		graph[i]=(int *)malloc(sizeof(int)*nodesize);
		for(int j=0;j<nodesize;j++)
			graph[i][j]=0;
	}
	return graph;
}

int **copy_matrix(int **graph,int nodesize){
	int **graph2=(int **)malloc(sizeof(int *)*nodesize);
	for(int i=0;i<nodesize;i++){
		graph2[i]=(int *)malloc(sizeof(int)*nodesize);
		for(int j=0;j<nodesize;j++)
			graph2[i][j]=graph[i][j];
	}
	return graph2;
}

int head,rear;
int queue[100];
int empty(void){
	return head==rear;
}
void enqueue(int item){
	queue[rear]=item;
	rear=(rear+1)%100;
}
int dequeue(void){
	int retval=queue[head];
	head=(head+1)%100;
	return retval;
}

int find_path(int **graph,int startnode,int endnode,int nodesize){
	enqueue(startnode);
	int prev[nodesize],visited[nodesize];
	for(int i=0;i<nodesize;i++){
		visited[i]=0;
		prev[i]=-1;
	}
	int cur;
	while(!empty()){
		cur=dequeue();
		if(cur==endnode)
			break;
		if(!visited[cur]){
			for(int i=0;i<nodesize;i++)
				if(graph[cur][i] && !visited[i]){
					enqueue(i);
					prev[i]=cur;
				}
			visited[cur]=1;
		}
	}
	while(!empty())
		dequeue();
	if(cur==endnode){
		int parent=prev[endnode];
		while(parent!=-1){
			graph[parent][cur]=0;
			cur=parent;
			parent=prev[cur];
		}
		return 1;
	}else
		return 0;	
}

void display_map(int **matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++)
			if(matrix[i][j])
			cout<<"matrix["<<i<<"]["<<j<<"]="<<matrix[i][j]<<endl;
	}
}

void show_match(int **copy_graph,int **graph,int size,
	map <int,string> machines,map <int,string> tasks){
	for(int i=1;i<size-1;i++){
		for(int j=1;j<size-1;j++){
			if(!graph[i][j] && copy_graph[i][j])
				cout<<machines[i]<<"->"<<tasks[j]<<endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	FILE *fp=fopen(argv[1],"r");
	int machinesize,tasksize;
	fscanf(fp,"%d\t%d\n",&machinesize,&tasksize);
	int **graph=init_map(machinesize+tasksize+2);
	
	map <string,int> string2int;
	map <int,string> machines;
	map <int,string> tasks;
	char buff[1024];
	char *machine_line=fgets(buff,sizeof(buff),fp);
	char *machine_name=strtok(machine_line,"\t\n");
	int i=1;
	while(machine_name){
		string2int[machine_name]=i;
		graph[0][i]=1;
		machines[i++]=machine_name;
		machine_name=strtok(NULL,"\t\n");
	}
	char *task_line=fgets(buff,sizeof(buff),fp);
	char *task_name=strtok(task_line,"\t\n");
	while(task_name){
		string2int[task_name]=i;
		graph[i][machinesize+tasksize+1]=1;
		tasks[i++]=task_name;
		task_name=strtok(NULL,"\t\n");
	}
	string node1,node2;
	while(fgets(buff,sizeof(buff),fp)!=NULL){
		node1=strtok(buff,"\t\n");
		node2=strtok(NULL,"\t\n");
		graph[string2int[node1]][string2int[node2]]=1;
	}
	fflush(fp);
	fclose(fp);

	int **copy_graph=copy_matrix(graph,machinesize+tasksize+2);

	int flag;
	while((flag=find_path(graph,0,machinesize+tasksize+1,machinesize+tasksize+2)))
		;
	show_match(copy_graph,graph,machinesize+tasksize+2,machines,tasks);
	
	return 0;
}