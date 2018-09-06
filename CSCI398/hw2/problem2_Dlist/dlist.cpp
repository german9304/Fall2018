#include<iostream>

using std::cout;
using std::endl;

#include "dlist.h"

//inserts a Node object into a list
void Dlist::insert(int st){
        Node *ptr_to_node = new Node( new int(st), NULL,  head);
        if(head == NULL)
                tail = ptr_to_node;
        else 
                head->prev = ptr_to_node;
        head = ptr_to_node;
        ptr_to_node = NULL;

        length++;
}//insert

void Dlist::print()const{
    Node *ptr = head;
    while(ptr != NULL){
        cout << *(ptr->value) << " ";
        ptr = ptr->next;
    }
	cout << endl;
}//print


void Dlist::clear(){
        Node *ptr = head;
        while(ptr != NULL){
                Node *temp = ptr;
                ptr = ptr->next;
                delete temp->value;
                delete temp;//deletes Node object
        }//while
		head = NULL;
		tail = NULL;
		length = 0;
}//clear()

//destructor of the class
Dlist::~Dlist(){
	clear();
}//destructor

void Dlist::print_reverse()const{
    Node *ptr = tail;
    while(ptr != NULL){
        cout << *(ptr->value) << " ";
        ptr = ptr->prev;
    }
	cout << endl;
}



