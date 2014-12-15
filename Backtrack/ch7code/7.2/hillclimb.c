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

int calc_weight(int (*target)[CUBE],int (*m)[CUBE]){
    int weight=0,i,j;
    for(i=0;i<CUBE;i++)
        for(j=0;j<CUBE;j++){
            if(m[i][j]==-1)
                continue;
            if(m[i][j]!=target[i][j])
                weight++;
        }
    return weight;
}

struct Node{
    int cube[CUBE][CUBE];
    int x;
    int y;
    int weight;
    struct Node *prev;
};
#define STACKSIZE 10000
struct Node *stack[STACKSIZE];
int sp=-1;
void push(struct Node *item){
    stack[++sp]=item;
}
struct Node *pop(void){
    return stack[sp--];
}
struct Node *top(void){
    return stack[sp];
}
int empty(void){
    return sp==-1;
}

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

void insertsort(struct Node **data,int size){
    int i,j;
    struct Node *pivot;
    for(i=1;i<size;i++){
        pivot=data[i];
        for(j=i-1;j>=0 && data[j]->weight < pivot->weight;j--)
            data[j+1]=data[j];
        data[j+1]=pivot;
    }
}

void hillclimbing(int (*cube)[CUBE],int x,int y,int (*target)[CUBE]){
    struct Node *currentnode=malloc(sizeof(struct Node));
    currentnode->x=x,currentnode->y=y,currentnode->prev=NULL;
    currentnode->weight=calc_weight(target,cube);
    cube_copy(cube,currentnode->cube);
    push(currentnode);
    struct Node *node;
    int tmpcube[CUBE][CUBE];
    int counter=0;
    struct Node *nodes[4];
    int nodesszie,i;
    while(!empty()){
        counter+=1;
        currentnode=top();
        cube_display(currentnode->cube);
        printf("************\n");
        if(cube_equal(currentnode->cube,target)){
            displayoutcome(currentnode);
            break;
        }
        pop();
        nodesszie=0;
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
                node->weight=calc_weight(target,node->cube);
                nodes[nodesszie++]=node;
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
                node->weight=calc_weight(target,node->cube);
                nodes[nodesszie++]=node;
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
                node->weight=calc_weight(target,node->cube);
                nodes[nodesszie++]=node;
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
                node->weight=calc_weight(target,node->cube);
                nodes[nodesszie++]=node;
            }
        }
        for(i=0;i<nodesszie;i++)
            push(nodes[i]);
    }
}

int main(int argc, char const *argv[]){
    int origin[CUBE][CUBE]={{2,3,-1},{1,8,5},{7,4,6}};
    int x=0,y=2;
    int target[CUBE][CUBE]={{1,2,3},{8,-1,4},{7,6,5}};
    hillclimbing(origin,x,y,target);
    return 0;
}