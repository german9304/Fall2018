
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


void List::merge(List &another){
  Node *cur = head;
  Node *curAnother = another.head;
  while(cur != NULL){
     int cur_value = cur->value;
     int another_value = curAnother->value;
     if(cur_value > another_value){
         Node * temp = cur;
         Node * temp2 = curAnother->next;
         if(cur == head){
            head = curAnother;
            head->next = cur;
            cur = head;
            another.head = temp2;
            curAnother = another.head;
         }

     }else if(cur_value < another_value){
        Node * temp = cur->next;
        Node * temp2 = curAnother->next;
        if(temp != NULL){
          if(temp->value >  curAnother->value){
          cur->next = curAnother;
          Node *nextn = cur->next;
          nextn->next = temp;
          another.head = temp2;
          curAnother = another.head;
          cur = nextn;
          if(curAnother == NULL){
            cur = NULL;
          }
        }else{
          cur = cur->next;
        }
      }else{
        cur->next = curAnother;
        Node *nextn = cur->next;
        nextn->next = NULL;
        another.head = temp2;
        curAnother = another.head;
        cur = nextn;
         if(curAnother == NULL){
            cur = NULL;
          }
      }

     }else{


     }
  }
}












