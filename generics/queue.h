#ifndef GENERICQUEUE_H_INCLUDED
#define GENERICQUEUE_H_INCLUDED

struct node{
    void *value;
    struct node *next;
};

int isEmpty();

void enqueue(void*, size_t);

void dequeue();

void* Front();

#endif // GENERICQUEUE_H_INCLUDED
