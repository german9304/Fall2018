#include<iostream>

#ifndef TNODE_H
#define TNODE_H

class Tnode{
        public:
                Tnode(): left(NULL), right(NULL), size(1) {};
				Tnode(int aval){
					value = aval;
					left = NULL;
					right = NULL;
					size = 1;
				};
                int value;
                Tnode* left;
                Tnode* right;
				int size;
};

#endif
