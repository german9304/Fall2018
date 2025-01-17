
#include "list.h"
using std::cout;
using std::endl;

//destructor of the class
//this function is called when List object is destroyed
List::~List(){
   Node *ptr = head;
   while(ptr != NULL){
        Node *temp = ptr;
        ptr = ptr->next;
        delete temp;//deletes Node object

   }//while
}//destructor

//inserts a Node object into a list
void List::insert(int st){
    Node *ptr_to_node = new Node(st, head);
    head = ptr_to_node;
    
    ptr_to_node = NULL;
    
    length++;
}//insert

//removes the front of the list
bool List::remove(){
    if(length == 0)
        return false;
    Node* temp = head;
    head = head->next;
    delete temp;
    temp = NULL;
    return true;
}//remove()

void List::print()const{
    Node *ptr = head;
    while(ptr != NULL){
       cout << ptr->value << " ";//returns int object
       ptr = ptr->next;
    }//while
	cout << endl;
}//print

void List::insert_sorted(int st){
    if(length == 0){
        head = new Node(st, NULL);
    }
    else{
       Node* temp = head;
       if(st < temp->value){
            head = new Node(st, head);
       }
       else{
            Node *next = temp->next;
            bool inserted = false;
            while(next != NULL){
                if(st < next->value){
                    temp->next = new Node(st, next);
                    inserted = true;
                    break;
                }
                temp = next;
                next = temp->next;
            }//while
            if(!inserted){//insert at the end of the list
                temp->next = new Node(st, next);
            }
       }//else
    }//else
    length++;
}//insert_sorted

void  List::printAlternate(int k){
  Node * ptr = head;
  alternate(ptr,k);
  if(iter%2 == 0){
     cout  << head->value <<endl;
  }
}

void  List::alternate(Node * ptr,int k){
    if(ptr == NULL){
      return;
    }
    ptr = ptr->next;
    alternate(ptr,k);
    if(ptr!=NULL){
      if(is){
        if(iter%2 == 0){
            cout  << ptr->value <<endl;
        }
      }
      if(iter == k && !is){
        cout  << ptr->value <<endl;
        iter = 0;
        is = true;
      }
       iter++;
    }

}

