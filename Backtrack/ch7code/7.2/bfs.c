#include <stdio.h>
#include <stdlib.h>
#define CUBE 3

int cube_equal(int (*m1)[CUBE],int (*m2)[CUBE]){
    int i,j,ok=1;
    for(i=0;i<CUBE && ok;i++)
        for(j=0;j<CUBE && ok;j++)
            if(m1[i][j]!=m2[i][j])
                ok=0;
    return ok;
}

void cube_copy(int (*source)[CUBE],int (*dest)[CUBE]){
    int i,j;
    for(i=0;i<CUBE;i++)
        for(j=0;j<CUBE;j++)
            dest[i][j]=source[i][j];
}

void cube_display(int (*m)[CUBE]){
    int i,j;
    for(i=0;i<CUBE;i++){
        for(j=0;j<CUBE;j++)
            printf("%d ",m[i][j]);
        printf("\n");
    }
}

void move_up(int (*m)[CUBE],int x,int y){
    m[x][y]=m[x-1][y],m[x-1][y]=-1;
}

void move_down(int (*m)[CUBE],int x,int y){
    m[x][y]=m[x+1][y],m[x+1][y]=-1;
}

void move_left(int (*m)[CUBE],int x,int y){
    m[x][y]=m[x][y-1],m[x][y-1]=-1;
}

void move_right(int (*m)[CUBE],int x,int y){
    m[x][y]=m[x][y+1],m[x][y+1]=-1;
}

struct Node{
    int cube[CUBE][CUBE];
    int x;
    int y;
    struct Node *prev;
};

void displayoutcome(struct Node *node){
    while(node){
        cube_display(node->cube);
        printf("^\n");
        printf("^\n");
        printf("^\n");
        node=node->prev;
    }
}

int inme(struct Node *node,int (*m)[CUBE]){
    int ok=0;
    while(node && !ok){
        if(cube_equal(node->cube,m))
            ok=1;
        node=node->prev;
    }
    return ok;
}

#define QSIZE 10000
struct Node *queue[QSIZE];
int head,rear;
int queue_empty(void){
    return head==rear;
}
int full(void){
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
struct Node *queue_top(void){
    return queue[head];
}

void bfs_search(int (*cube)[CUBE],int x,int y,int (*target)[CUBE]){
     struct Node *currentnode=malloc(sizeof(struct Node));
    currentnode->x=x,currentnode->y=y,currentnode->prev=NULL;
    cube_copy(cube,currentnode->cube);
    enqueue(currentnode);
    struct Node *node;
    int tmpcube[CUBE][CUBE];
    int counter=0;
    while(!queue_empty()){
        currentnode=queue_top();
        if(cube_equal(currentnode->cube,target)){
            printf("One method .....\n");
            displayoutcome(currentnode);
            counter+=1;
            //break;
        }
        dequeue();
        //up
        cube_copy(currentnode->cube,tmpcube);
        if(currentnode->x > 0){
            move_up(tmpcube,currentnode->x,currentnode->y);
            if(!inme(currentnode,tmpcube)){
             //   printf("UP!\n");
                node=malloc(sizeof(struct Node));
                cube_copy(tmpcube,node->cube);
                node->x=currentnode->x-1,node->y=currentnode->y;
                node->prev=currentnode;
                enqueue(node);
            }
        }
        //down
        cube_copy(currentnode->cube,tmpcube);
        if(currentnode->x <CUBE-1){
            move_down(tmpcube,currentnode->x,currentnode->y);
            if(!inme(currentnode,tmpcube)){
                //printf("DOWN!\n");
                node=malloc(sizeof(struct Node));
                cube_copy(tmpcube,node->cube);
                node->x=currentnode->x+1,node->y=currentnode->y;
                node->prev=currentnode;
                enqueue(node);
            }
        }
        //left
        cube_copy(currentnode->cube,tmpcube);
        if(currentnode->y > 0){
           move_left(tmpcube,currentnode->x,currentnode->y);
            if(!inme(currentnode,tmpcube)){
               // printf("LEFT\n");
                node=malloc(sizeof(struct Node));
                cube_copy(tmpcube,node->cube);
                node->x=currentnode->x,node->y=currentnode->y-1;
                node->prev=currentnode;
                enqueue(node);
            }
        }
        //right
        cube_copy(currentnode->cube,tmpcube);
        if(currentnode->y < CUBE-1){
            move_right(tmpcube,currentnode->x,currentnode->y);
            if(!inme(currentnode,tmpcube)){
               // printf("RIGHT\n");
                node=malloc(sizeof(struct Node));
                cube_copy(tmpcube,node->cube);
                node->x=currentnode->x,node->y=currentnode->y+1;
                node->prev=currentnode;
                enqueue(node);
            }
        }
    }
    printf("Total %d methods\n",counter);
}

int main(int argc, char const *argv[]){
    int origin[CUBE][CUBE]={{2,3,-1},{1,8,5},{7,4,6}};
    int x=0,y=2;
    int target[CUBE][CUBE]={{1,2,3},{8,-1,4},{7,6,5}};
    bfs_search(origin,x,y,target);
    return 0;
}