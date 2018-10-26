#include<iostream>
using namespace std;
#define MAX 101
int A[MAX];
int front=-1;
int rear=-1;
bool isEmpty()
{
    if(front==-1&&rear==-1)
    return true;

    return false;
}
bool isFull()
{
    if((rear+1)%MAX==front)
    return true;

    return false;
}
void Enqueue(int x)
{
    if(isFull())
    return;
    if(isEmpty())
    {
        front=0;
        rear=0;
    }
    else
    {
        rear=(rear+1)%MAX;
    }
    A[rear]=x;
}
void Dequeue()
{
    if(isEmpty())
    return;
    else if(front==rear)
    front=rear=-1;
    else
    front=(front+1)%MAX;
}
int Front()
{
    if(front==-1)
    return -1;

    return A[front];
}
void Print()
{
    int count =(rear-front+MAX)%MAX+1;
    for(int i=0;i<count;i++)
    {
        int index=(front+i)%MAX;
        cout<<A[index]<<" ";
    }
    cout<<"\n";
}
int main()
{
    Enqueue(2); Print();
    Enqueue(4); Print();
    Enqueue(6); Print();
    Dequeue(); Print();
    Enqueue(8); Print();
    return 0;
}