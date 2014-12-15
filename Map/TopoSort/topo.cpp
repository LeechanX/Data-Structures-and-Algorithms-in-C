#include <iostream>
#include <map>
#include <stack>
#include "map.h"
#define QSIZE 100
#define N 100
using namespace std;

int head,rear;
int queue[QSIZE];
int empty(void){
	return head==rear;
}
int full(void){
	return head=(rear+1)%QSIZE;
}
void enqueue(int item){
	queue[rear]=item;
	rear=(rear+1)%QSIZE;
}
int dequeue(void){
	int retval=queue[head];
	head=(head+1)%QSIZE;
	return retval;
}

void topo_base_method(struct Graph *graph,map <int,string> node_hash){
	map <int,int> indgrees;
	int i;
	struct Node *cur;
	for(i=0;i<graph->nodesize;i++){
		cur=graph->nodes[i]->next;
		while(cur){
			if(indgrees.count(cur->vertex))
				indgrees[cur->vertex]++;
			else
				indgrees[cur->vertex]=1;
			cur=cur->next;
		}
	}
	
	for(i=0;i<graph->nodesize;i++)
		if(!indgrees[i])
			enqueue(i);

	int indgree0;
	while(!empty()){
		indgree0=dequeue();
		cout<<node_hash[indgree0]<<" ";
		cur=graph->nodes[indgree0]->next;
		while(cur){
			indgrees[cur->vertex]--;
			if(!indgrees[cur->vertex])
				enqueue(cur->vertex);
			cur=cur->next;
		}
	}
	cout<<endl;
	for(i=0;i<graph->nodesize;i++){
		if(indgrees[i]){
			cout<<"有环。"<<endl;
			break;
		}
	}
}


stack<string> mystack;
void dfs(struct Graph *graph,int startnode,int *visited,map <int,string> node_hash){
	if(visited[startnode]==2)
		return;
	if(visited[startnode]==1){
		cout<<"有环。"<<endl;
		return;
	}
	struct Node *cur=graph->nodes[startnode]->next;
	//cout<<node_hash[startnode]<<" ";
	visited[startnode]=1;
	while(cur){
		dfs(graph,cur->vertex,visited,node_hash);
		cur=cur->next;
	}
	visited[startnode]=2;
	mystack.push(node_hash[startnode]);
}

void topo_use_dfs(struct Graph *graph,map <int,string> node_hash){
	int visited[N]={};
	int i;
	for(i=0;i<graph->nodesize;i++)
		if(!visited[i])
			dfs(graph,i,visited,node_hash);
	while(!mystack.empty()){
		cout<<mystack.top()<<" ";
		mystack.pop();
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	if(argc<2){
		printf("Wrong input\n");
		return 1;
	}
	map <int,string> node_hash;
	struct Graph *graph=read_map(argv[1],&node_hash);
	display_debug(graph);
	topo_base_method(graph,node_hash);
	topo_use_dfs(graph,node_hash);
	return 0;
}