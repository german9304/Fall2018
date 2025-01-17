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


int BST::previous(int val){
    Tnode * rootn = root;
    int max = INT_MIN;
    previousNode(rootn, val, max);
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

int  BST::countSum(){
     Tnode * cur = root;
     int sum = 0;
     std::queue<Node> aq;
     sumNodes(cur,sum,aq);
     return sum;
}

void BST::iterate(Tnode * rootn, int & total_sum){
    if(rootn != NULL){
    total_sum+= rootn->value;
    iterate(rootn->left,total_sum);
    iterate(rootn->right, total_sum);
    }
}
 void BST::sumNodes(Tnode * rootn, int & sum, std::queue<Node> & aq){
   Node an;
   an.node = rootn;
   an.sum = root->value;
   aq.push(an);
   int res = 0;
   int n1 = 0;
   int n2 = 0;
   int res2 = 0;
   while(!aq.empty()){
    Node an = aq.front();
    Tnode * tn = an.node;
     if(tn != NULL){ 
       if(tn->left != NULL){
        iterate(tn->left,res);
        }
        if(tn->right != NULL){
        iterate(tn->right,res2);
        }
      if(tn != root){
        if(res == an.sum  ){
          sum++;
        }
        if(res2 == an.sum){
          sum++;
        }
      }

        res = 0;
        res2 = 0;
        if(tn->left != NULL){
          n1 =  an.sum + tn->left->value;
        }
        if(tn->right != NULL){
          n2 = an.sum + tn->right->value;
        }
        Node temp; 
        temp.node = tn->left;
        temp.sum = n1;
        Node temp2;
        temp2.node =tn->right;
        temp2.sum = n2;
        aq.push(temp);
        aq.push(temp2);
     }
      aq.pop();
   }
 }





