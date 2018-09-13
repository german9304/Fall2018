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


void Dlist::partition(const int pivot){
    Node * h = head;
    Node * t = tail;
    partition(h, t, pivot);
}

void Dlist::partition(Node * h, Node *t, const int pivot){
    if(h == NULL || t == NULL || h == t ){
      return;
    }
    if(h != NULL){
     if(*(h->value) < pivot){
       h = h->next;
      }
    }
    if(t != NULL){
        if(*(t->value) > pivot){
           t = t->prev;
        }
    }
    if(t != NULL && h!= NULL){
       if(*(t->value) < pivot && *(h->value) > pivot){
        int tvalue = *(t->value);
        *(t->value) = *(h->value);
        *(h->value) = tvalue;
         h = h->next;
         t = t->prev;
         if(h->prev == t && t->next == h){
            t = NULL; 
            h = NULL;
         }
       }
    }

    partition(h, t, pivot);
}



