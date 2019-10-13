#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//defining global structure for the node
typedef struct number{
    int no;
    struct number *next;
}Num;

//start struct pointer. This pointer will always point to the first node in the list
Num *start = NULL;

//Functoin declaration
Num* createNode();
void insert(int);
void insertAtBeg(Num*);
void insertAtEnd(Num*,Num*);
void deleteNode(int);
int view();

//function defination
Num* createNode(){
    Num *temp;
    temp = (Num*)malloc(sizeof(Num));
    temp->next = NULL;
    return (temp);
}

void insert(int num){
    int status = 0;
    
    /*creating new node using createNode() and assigning value to it*/    
    Num *newNode;
    newNode = createNode();
    newNode->no = num;
    
    if(start == NULL)                       //if the list is empty
        start = newNode;
    else{
        if(start->no > num)                  
            insertAtBeg(newNode);
        /*if the first node of the list has the number greater than the current number than
        the newNode will become the first node of the list*/
        else{       
        //traversing through the node for finding the number less than the current number.
            Num *tempNode,*destNode = NULL;
            /*destNode is the node which the number just smaller than the current number
              tempNode is the node which has the number just bigger than the current number*/
            tempNode = start;
            
            while(tempNode->no < num){
                
                if(tempNode->next == NULL){   //if the pointer has reached the last node
                    status = 1;
                    break;
                }
            
            destNode = tempNode;              
            tempNode = tempNode->next;
            }
                               
        //if the point of insertion is in between
        if(status == 0){
            destNode->next = newNode;
            newNode->next = tempNode;
        }
        //if the point of the insertion is at the end of the node
        else if(status == 1){
            insertAtEnd(newNode,tempNode);
        }
        
        }
    }
}

void insertAtBeg(Num *newNode){
    newNode->next = start;
    start = newNode;
}

void insertAtEnd(Num *newNode,Num *lastNode){
    lastNode->next = newNode;
}

void deleteNode(int num){
    Num *destNode,*tempNode;
    destNode = start;
    if(start->no == num){               //if the first node has the req number
        start = start->next;
    }else{
        //tarvesing to the node which is having the required number
        while(destNode->no != num){
            tempNode = destNode;
            destNode = destNode->next;
        }
    
        tempNode->next = destNode->next;
    }
    //removing the allocated memory by malloc
    free(destNode);
}

int view(){
    if(start == NULL){
        printf("List is empty");
        return (NULL);   
    }
    else{
        Num *tempNode;
        tempNode = start;
        printf("\nElements of List: ");
        while(tempNode != NULL){
            printf("%d ",tempNode->no);
            tempNode = tempNode->next;
        }
        return (1);       
    }
    
}

//main function
int main(){
    int choice = 0 , no;
    
    while(1){
        system("cls");
        printf("1) Insert\n");
        printf("2) Delete\n");
        printf("3) View\n");
        printf("4) Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);  
        
        switch(choice){
            case 1:
                printf("Enter number: ");
                scanf("%d",&no);
                insert(no);
                view();
                break;
            case 2:
                no = view();
                if(no != NULL){
                    printf("\nEnter number you want to remove: ");
                    scanf("%d",&no);
                    deleteNode(no);
                    view();    
                }
                break;
            case 3:
                view();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid Input");
        }
        getch();  
    }
    
    return (0);
}
