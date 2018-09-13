#include<iostream>

#ifndef NODE_H
#define NODE_H

class Node{
        public:
                Node():  value(NULL), prev(NULL), next(NULL) {};
                Node(int *st, Node* pr, Node* n){
					value = st;
					prev = pr;
					next = n;
		};
                int* value;
                Node* prev;
                Node* next;
};

#endif
