
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
         Node * cur_temp = cur;
         Node * another_temp = curAnother->next;
         if(cur == head){
            head = curAnother;
            head->next = cur_temp;
            Node *th = head;
            cur = th;
            another.head = another_temp;
            curAnother = another.head;
         }

     }else if(cur_value < another_value){
        Node * cur_temp = cur->next;
        Node * another_temp = curAnother->next;
        if(cur_temp != NULL){
          if(cur_temp->value >  curAnother->value){
          cur->next = curAnother;
          Node *nextn = cur->next;
          nextn->next = cur_temp;
          another.head = another_temp;
          curAnother = another.head;
          cur = nextn;
        }else if(cur_temp->value == curAnother->value){
             cur->next = curAnother;
             Node *nextn = cur->next;
             nextn->next = cur_temp;
             another.head = another_temp;
             cur = cur_temp;
             curAnother = another.head;
        }else{
          cur = cur->next;
        }
      }else{
        cur->next = curAnother;
        Node *nextn = cur->next;
        nextn->next = NULL;
        another.head = another_temp;
        curAnother = another.head;
        cur = nextn;
      }

     }else{
      Node * cur_temp = cur->next;
      Node * another_temp = curAnother->next;
      cur->next = curAnother;
      Node *nextn = cur->next;
      nextn->next = cur_temp;
      cur = nextn;
      another.head = another_temp;
      curAnother = another.head;
     }
      if(curAnother == NULL){
            cur = NULL;
          }
  }
}











