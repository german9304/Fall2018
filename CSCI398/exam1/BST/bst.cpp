#include<iostream>
using namespace std;

#include "bst.h"
	

Tnode* BST::balance(Tnode *cur){
								int bf = balanceFactor(cur);
								if(bf > 1){//left subtree is higher
									if(getHeight(cur->left->left) >= getHeight(cur->left->right)){
										cur = rightRotation(cur);//height is updated
									}//outside case
									else{
										cur->left = leftRotation(cur->left);
										cur = rightRotation(cur);
									}//inside case
								}//bf = 2
								else if(bf < -1){
									if(getHeight(cur->right->right) >= getHeight(cur->right->left)){
										cur = leftRotation(cur);
									}//outside case
									else{
										cur->right = rightRotation(cur->right);
										cur = leftRotation(cur);
									}
								}//if bf = -2
								else{
									updateHeight(cur);
									updateSize(cur);
								}
								return cur;
}
Tnode* BST::remove(Tnode* cur, string ak){
	if(cur == NULL)
		return NULL;
	if(ak < cur->key){
		cur->left = remove(cur->left, ak);
		cur = balance(cur);
	}else if(ak > cur->key){
		cur->right = remove(cur->right, ak);
		//restore balance
		cur = balance(cur);
								
	}else{//found the key
		if(cur->left == NULL){
			Tnode* temp = cur->right;
			delete cur;
			return temp;
		}else if(cur->right == NULL){
			Tnode* temp = cur->left;
			delete cur;
			return temp;
		}else{
			Tnode *leftMost = getLeftmost(cur->right);
			cur->key = leftMost->key;
			cur->value = leftMost->value;
			cur->right = remove(cur->right, leftMost->key);
			//restore balance
			cur = balance(cur);	
		}//two children
	
	}//found key
	return cur;
}//remove

Tnode* BST::getLeftmost(Tnode* cur){
	if(cur == NULL)
		return NULL;
	if(cur->left == NULL)
		return cur;
	return getLeftmost(cur->left);
}//getLeftmost

void BST::updateHeight(Tnode *cur){
	if(cur == NULL)
		return;
	int hl = -1, hr = -1;
	if(cur->left != NULL)
		hl = cur->left->height;
	if(cur->right != NULL)
		hr = cur->right->height;
	cur->height = (hl > hr) ? (hl + 1) : (hr + 1);

}//updateHeight
				
int BST::balanceFactor(Tnode *cur){
	int hl = -1, hr = -1;
	if(cur->left != NULL)
		hl = cur->left->height;
	if(cur->right != NULL)
		hr = cur->right->height;
	return (hl - hr);
}
				
Tnode* BST::rightRotation(Tnode *cur){
	Tnode *L = cur->left;
	cur->left = L->right;
	updateHeight(cur);
	updateSize(cur);
	L->right = cur;
	updateHeight(L);
	updateSize(L);
	return L;
}

Tnode* BST::leftRotation(Tnode *cur){
	Tnode *R = cur->right;
	cur->right = R->left;
	updateHeight(cur);
	updateSize(cur);
	R->left = cur;
	updateHeight(R);
	updateSize(R);
	return R;
}

void BST::heightPrint(Tnode *cur){
	if(cur != NULL){
		heightPrint(cur->left);
		cout << cur->height << " ";
		heightPrint(cur->right);
	}

}

void BST::print_inorder(Tnode *cur){
        if(cur == NULL)
                return;
        print_inorder(cur->left);
        cout << "(" << cur->key << "){";
		int asize = (int)(cur->value).size();
		for(int i = 0; i < asize; i++)
			cout << (cur->value)[i] << " " ;
		cout << "} ";
        print_inorder(cur->right);
}//print_inorder


void BST::clean(Tnode *cur){
        if(cur == NULL)
                return;
        clean(cur->left);
        clean(cur->right);
        delete cur;
}//clean()

Tnode* BST::insert(Tnode *cur, string akey, string aval){
               if(akey < cur->key){
                        if(cur->left == NULL){
                                cur->left = new Tnode(akey, aval);
								updateHeight(cur);
								updateSize(cur);
                                }//if found place
                        else{
                                cur->left = insert(cur->left, akey, aval);
								cur = balance(cur);
						}//else
						
                }//if 
                else if(akey > cur->key){
                        if(cur->right == NULL){
                                cur->right = new Tnode(akey, aval);
								updateHeight(cur);
								updateSize(cur);
                                }
                        else{
                                cur->right = insert(cur->right, akey, aval);
								cur = balance(cur);
						
						}
						
                }//else if
                else{
					(cur->value).push_back(aval);
                        }

				return cur;
      
}//insert()


//Test 1 Problem 2
void BST::printPath(int k){
   Tnode * cur = root;
   Tnode * knode = NULL;
   traversal(cur, k, knode);
   printKthPath(cur, knode);

}

void BST::traversal(Tnode *cur, int k, Tnode * &knode){
   if(cur == NULL){
     return;
   }
   traversal(cur->left,k, knode);
   if(iter == k){
      knode = cur;
   }
   iter++;
   traversal(cur->right,k,knode);
}
void BST::printKthPath(Tnode * cur, Tnode * knode){
  if(cur->key == knode->key){
  	cout << cur->key << endl;
     return;
  }
  if(cur->key > knode->key){
  	cout << cur->key << endl;
    printKthPath(cur->left,knode);
  }
  if(cur->key < knode->key){
  	cout << cur->key << endl;
    printKthPath(cur->right,knode);
  }
}

