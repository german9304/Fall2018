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
    int iter = 1;
    bool is = false;


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
	
	/*Test 1, Problem 1
		Write a recursive member function (public and private versions) that
		given an integer k, it will print out values of alternating nodes backward
		starting with the k-th node from the back (tail) of the list. 
		There is no tail pointer in List class.
	*/
	void printAlternate(int k);
    void  alternate(Node * ptr,int k);
	//you may pass whatever parameters you want to the private member function "printAlternate"
};

#endif
