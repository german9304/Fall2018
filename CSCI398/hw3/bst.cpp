#include<iostream>
#include<climits>

using std::string;
using std::cout;
using std::endl;

#include "bst.h"

void BST::print_inorder(Tnode *cur){
        if(cur == NULL)
                return;
        print_inorder(cur->left);
        cout << cur->value <<  " "  ;
        print_inorder(cur->right);
}//print_inorder

void BST::clean(Tnode *cur){
        if(cur == NULL)
                return;
        clean(cur->left);
        clean(cur->right);
        delete cur;
}//clean()

bool BST::insert(Tnode *cur, int aval){
			  
               if(aval < cur->value){
                        if(cur->left == NULL){
                                cur->left = new Tnode(aval);
								cur->size = cur->size + 1;
                                return true;
                                }
                        else{
                                bool res = insert(cur->left, aval);
								if(res)
									cur->size = cur->size + 1;
								return res;
								
						}
                }//if 
                else if(aval > cur->value){
                        if(cur->right == NULL){
                                cur->right = new Tnode(aval);
								cur->size = cur->size + 1;
                                return true;
                                }
                        else{
                                bool res = insert(cur->right, aval);
								if(res)
									cur->size = cur->size + 1;
								return res;
						}
                }//else if
                else{
                        return false;//only distinct integers are allowed
                }      
}//insert()

Tnode* BST::findLeftmost(Tnode* r){
	if(r == NULL)
		return NULL;
	if(r->left != NULL)
		return findLeftmost(r->left);
	else
		return r;
}

Tnode* BST::findRightmost(Tnode* r){
	if(r == NULL)
		return NULL;
	if(r->right != NULL)
		return findRightmost(r->right);
	else
		return r;
}


int BST::countSum(){
   return 0;
}
int BST::previous(int val){
    Tnode * rootn = root;
    int max = INT_MIN;
    previousNode(rootn, val, max);
    //cout << "node val: " << max <<endl;
    //cout <<"min: " <<  INT_MIN <<endl;
   return max;
}

void BST::previousNode(Tnode *root_node, int val, int & max){
    if(root_node == NULL){
      return;
    }
    if(root_node->value > val){
        previousNode(root_node->left,val,max);
    }
    if(root_node->value < val){
        //cout << root_node->value  <<endl;
        if(root_node->value  > max){
          max = root_node->value;
        }
        previousNode(root_node->right,val,max);
    }
       previousNode(root_node->left,val,max);
    
}


