#include<iostream>

#ifndef NODE_H
#define NODE_H

class Node{
    public:
    Node():  value(0), next(NULL) {};
    Node(int st, Node* ptr): value(st), next(ptr) {};
    int value;
    Node* next;
};
#endif
