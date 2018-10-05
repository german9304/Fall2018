#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef TNODE_H
#define TNODE_H


class Tnode{
        public:
                Tnode(): left(NULL), right(NULL) {};
				Tnode(string akey, string aval){
					key = akey;
					value.push_back(aval);
					height = 0;
					left = NULL;
					right = NULL;
					size = 1;
				};
                string key;
				vector<string> value;
				int height;
                Tnode* left;
                Tnode* right;
				int size;
};

#endif
