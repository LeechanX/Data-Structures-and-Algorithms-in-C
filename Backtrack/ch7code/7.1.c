#include <stdio.h>
#include <stdlib.h>
#define NODESIZE 7
#define STARTNODE 0
#define QSIZE 1000

struct Node{
    int vertex;
    int height;
    struct Node *prev;
};

struct Node *queue[QSIZE];
int head,rear;
int qempty(void){
    return head==rear;
}
int qfull(void){
    return head==(rear+1)%QSIZE;
}
void enqueue(struct Node *item){
    queue[rear]=item;
    rear=(rear+1)%QSIZE;
}
struct Node *dequeue(void){
    struct Node *retval=queue[head];
    head=(head+1)%QSIZE;
    return retval;
}

int isneibor(int (*map)[NODESIZE],int node1,int node2){
    return map[node1][node2];
}

void getneibors(int (*map)[NODESIZE],int node,int *neibors,int *size){
    int counter=0,i;
    for(i=0;i<NODESIZE;i++)
        if(map[node][i])
            neibors[counter++]=i;
    *size=counter;
}

void displayoutcome(int *answer){
    int i;
    for(i=0;i<NODESIZE;i++)
        printf("%d ", answer[i]);
    printf("%d\n",STARTNODE );
}

int inme(struct Node *node,int who){
    int ok=0;
    while(node && !ok){
        if(node->vertex==who)
            ok=1;
        node=node->prev;
    }
    return ok;
}

void displayout_come(struct Node *node){
    printf("%d ",STARTNODE );
    while(node){
        printf("%d ",node->vertex );
        node=node->prev;
    }
    printf("\n");
}

void bfs_search(int (*map)[NODESIZE]){
    int i,step;
    struct Node *currentnode=malloc(sizeof(struct Node));
    currentnode->vertex=STARTNODE,currentnode->prev=NULL,currentnode->height=0;
    enqueue(currentnode);
    int neibors[NODESIZE],neiborsize;
    struct Node *node;
    while(!qempty()){
        currentnode=dequeue();
        step=currentnode->height;
        if(step==NODESIZE-1 && isneibor(map,currentnode->vertex,STARTNODE)){
            displayout_come(currentnode);
            //break;
        }
        getneibors(map,currentnode->vertex,neibors,&neiborsize);
        for(i=0;i<neiborsize;i++)
            if(!inme(currentnode,neibors[i])){
                node=malloc(sizeof(struct Node));
                node->height=step+1,node->prev=currentnode,node->vertex=neibors[i];
                enqueue(node);
            }
    }
}
#define STACKSIZE 100
struct Node *stack[STACKSIZE];
int sp=-1;
int sempty(void){
    return sp==-1;
}
void push(struct Node *item){
    stack[++sp]=item;
}
struct Node *pop(void){
    return stack[sp--];
}
struct Node *top(void){
    return stack[sp];
}

void dfs_search(int (*map)[NODESIZE]){
    struct Node *currentnode=malloc(sizeof(struct Node));
    currentnode->vertex=STARTNODE,currentnode->height=0,currentnode->prev=NULL;
    push(currentnode);
    int neiborsize,neibors[NODESIZE],i;
    struct Node *node;
    while(!sempty()){
        currentnode=top();
        if(currentnode->height==NODESIZE-1 && isneibor(map,currentnode->vertex,STARTNODE)){
            displayout_come(currentnode);
            //break;
        }
        pop();
        getneibors(map,currentnode->vertex,neibors,&neiborsize);
        for(i=0;i<neiborsize;i++)
            if(!inme(currentnode,neibors[i])){
                node=malloc(sizeof(struct Node));
                node->vertex=neibors[i],node->height=currentnode->height+1,node->prev=currentnode;
                push(node);
            }
    }
}

void backtrace(int (*map)[NODESIZE],int *answer,int step,int *visited){
    if(step==NODESIZE && isneibor(map,answer[step-1],STARTNODE)){
        displayoutcome(answer);
        return;
    }
    int myneibor[NODESIZE],neiborsize,currentnode=answer[step-1],i;
    getneibors(map,currentnode,myneibor,&neiborsize);
    for(i=0;i<neiborsize;i++)
        if(!visited[myneibor[i]]){
            answer[step]=myneibor[i];
            visited[myneibor[i]]=1;
            backtrace(map,answer,step+1,visited);
            visited[myneibor[i]]=0;
        }
}

int main(){
    int map[NODESIZE][NODESIZE]={
        {0,1,0,0,0,1,1},
        {1,0,0,0,0,1,0},
        {0,0,0,1,1,0,0},
        {0,0,1,0,1,0,1},
        {0,0,1,1,0,1,0},
        {1,1,0,0,1,0,0},
        {1,0,0,1,0,0,0}
    };
    int answer[NODESIZE];
    answer[0]=STARTNODE;
    int visited[NODESIZE]={};
    visited[STARTNODE]=1;
    printf("use backtrace:\n");
    backtrace(map,answer,1,visited);
    printf("use DFS:\n");
    dfs_search(map);
    printf("use BFS:\n");
    bfs_search(map);
}