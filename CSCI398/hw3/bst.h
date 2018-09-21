
#include "tnode.h"
#ifndef BST_H
#define BST_H
#include <queue>
class BST{
        public:
                BST():  root(NULL) {};
                ~BST(){ clean(root); root = NULL; };
                class Node{
				public:
					Tnode *node;
					int sum = 0;
				};
				void insert(int aval){
					if(root == NULL){
						root = new Tnode(aval);
						return;
					}
					insert(root, aval);				
				};
                int countSum();
                void sumNodes(Tnode * rootn,  int &sum, std::queue<Node>  &aq);
                void iterate(Tnode * rootn, int & total_sum);
                int previous(int val);
                void previousNode(Tnode *root_node, int val, int& max);
				void print_inorder(){ print_inorder(root);
                        cout << endl;
				};
				int size(){ return root->size; }

		private:
				Tnode *root = NULL;		
				bool insert(Tnode *cur, int aval);
				void print_inorder(Tnode *cur);
				void clean(Tnode* cur);
				Tnode* findLeftmost(Tnode *cur);
				Tnode* findRightmost(Tnode *cur);
				
};


#endif
