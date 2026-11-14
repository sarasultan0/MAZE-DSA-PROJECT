#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Position.h"

using namespace std;

class Queue
{
private:

    Position* arr;
    int front;
    int rear;
    int capacity;
    int count;

public:

    Queue(int size);

    void enqueue(Position p);

    Position dequeue();

    bool isEmpty();

    bool isFull();

    void resize();

    ~Queue();
};

#endif
