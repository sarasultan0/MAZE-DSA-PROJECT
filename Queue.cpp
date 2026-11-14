
#include "Queue.h"

Queue::Queue(int size)
{
    if(size<=0)
        size=5;

    capacity=size;
    front=0;
    rear=-1;
    count=0;

    arr=new Position[capacity];
}

void Queue::enqueue(Position p)
{
    if(isFull())
    {
        resize();
    }

    rear=(rear+1)%capacity;
    arr[rear]=p;
    count++;
}

Position Queue::dequeue()
{
    if(isEmpty())
    {
        Position p;
        p.row=-1;
        p.col=-1;
        return p;
    }

    Position p=arr[front];

    front=(front+1)%capacity;

    count--;

    return p;
}

bool Queue::isEmpty()
{
    return count==0;
}

bool Queue::isFull()
{
    return count==capacity;
}

void Queue::resize()
{
    int newCapacity=capacity*2;

    Position* newArr=new Position[newCapacity];

    for(int i=0;i<count;i++)
    {
        newArr[i]=arr[(front+i)%capacity];
    }

    delete[] arr;

    arr=newArr;
    capacity=newCapacity;
    front=0;
    rear=count-1;
}

Queue::~Queue()
{
    delete[] arr;
}

