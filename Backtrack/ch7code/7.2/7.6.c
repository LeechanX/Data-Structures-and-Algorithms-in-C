#include <stdio.h>
#include <stdlib.h>
#define CUBE 3
#define HEAPSIZE 100


struct Node{
    int g;
    int f;
    int x;
    int y;
    int cube[CUBE][CUBE];
    struct Node *prev;
};

#define HEAPSIZE 100
struct Heap{
    int size;
    int capacity;
    struct Node **data;
};
int heap_empty(struct Heap *heap){
    return heap->size==0;
}
void heap_swap(struct Heap *heap,int pos1,int pos2){
    struct Node *tmp=heap->data[pos1];
    heap->data[pos1]=heap->data[pos2];
    heap->data[pos2]=tmp;
}
void heap_hold(struct Heap *heap,int pos){
    int left=2*pos+1,right=2*pos+2;
    int minpos=pos;
    if(right<heap->size && heap->data[right]->f < heap->data[minpos]->f)
        minpos=right;
    if(left<heap->size &&  heap->data[left]->f < heap->data[minpos]->f)
        minpos=left;
    if(minpos!=pos){
        heap_swap(heap,minpos,pos);
        heap_hold(heap,minpos);
    }
}
struct Heap *init_heap(void){
    struct Heap *heap=malloc(sizeof(struct Heap));
    heap->size=0,heap->capacity=HEAPSIZE;
    heap->data=malloc(sizeof(struct Node*)*heap->capacity);
    return heap;
}

void insert_heap(struct Heap *heap,struct Node *new){
    int currentpos=heap->size,parent;
    heap->data[heap->size++]=new;
    while((parent=(currentpos-1)/2)>=0){
        if(heap->data[currentpos]->f >= heap->data[parent]->f)
            break;
        heap_swap(heap,currentpos,parent);
    }
}

struct Node *delete_min(struct Heap *heap){
    if(heap_empty(heap))
        return NULL;
    struct Node *retval=heap->data[0];
    heap->data[0]=heap->data[--(heap->size)];
    heap_hold(heap,0);
    return retval;
}

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

void astar(int (*cube)[CUBE],int x,int y,int (*target)[CUBE]){
    struct Node *currentnode=malloc(sizeof(struct Node)),*node;
    currentnode->x=x,currentnode->y=y,currentnode->prev=NULL;
    currentnode->g=0,currentnode->f=0;
    cube_copy(cube,currentnode->cube);
    struct Heap *heap=init_heap();
    insert_heap(heap,currentnode);
    
    int tmpcube[CUBE][CUBE];
    int counter=0,h;
    while(!heap_empty(heap)){
        counter+=1;
        currentnode=delete_min(heap);
      
        if(cube_equal(currentnode->cube,target)){
            displayoutcome(currentnode);
            break;
        }
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
                node->g=currentnode->g+1;
                h=calc_weight(target,node->cube);
                node->f=node->g+h;
                insert_heap(heap,node);
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
                node->g=currentnode->g+1;
                h=calc_weight(target,node->cube);
                node->f=node->g+h;
                insert_heap(heap,node);
            }
        }
        //left
        cube_copy(currentnode->cube,tmpcube);
        if(currentnode->y > 0){
           move_left(tmpcube,currentnode->x,currentnode->y);
            if(!inme(currentnode,tmpcube)){
                node=malloc(sizeof(struct Node));
                cube_copy(tmpcube,node->cube);
                node->x=currentnode->x,node->y=currentnode->y-1;
                node->prev=currentnode;
                node->g=currentnode->g+1;
                h=calc_weight(target,node->cube);
                node->f=node->g+h;
                insert_heap(heap,node);
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
                node->g=currentnode->g+1;
                h=calc_weight(target,node->cube);
                node->f=node->g+h;
                insert_heap(heap,node);
            }
        }
    }
}

int main(int argc, char const *argv[]){
    int origin[CUBE][CUBE]={{2,3,-1},{1,8,5},{7,4,6}};
    int x=0,y=2;
    int target[CUBE][CUBE]={{1,2,3},{8,-1,4},{7,6,5}};
    astar(origin,x,y,target);
    return 0;
}