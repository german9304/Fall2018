#include<iostream>
#include<string>
using namespace std;
#ifndef LIST_H
#define LIST_H

#include "node.h"

class List{
    private:
    Node *head;
    int length;
    public:
    List(): head(NULL), length(0) {};
    ~List();
    int size()const{ return length; };
    //inserts a Node in front of the list
    void insert(int st);
    //prints all Students in the list 
    void print()const;
    void insert_sorted(int st);
    //removes the front of the list
    bool remove();
	//merges the given list (on which it is called) with the list
	//given as a parameter. At the end the parameter list is empty,
	//and the list, on which this function is called, has both lists.
	void merge(List &another);
};

#endif
