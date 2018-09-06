#include "node.h"

#ifndef DLIST_H
#define DLIST_H

class Dlist{
        private:
                Node *head = NULL;
                Node *tail = NULL;
                int length;
        public:
                Dlist(): head(NULL), tail(NULL), length(0) {};
				void clear();
				~Dlist();

                int size()const { return length; };
                //inserts a Node in front of the list
                void insert(int st);
                //prints all Students in the list 
                void print()const;
				void print_reverse() const;
                //public "partition":
				void partition(const int pivot);
//private member function recursive "partition":
//void partition( use any parameters that you need );

};

#endif

