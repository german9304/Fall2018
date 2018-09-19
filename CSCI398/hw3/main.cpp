#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;

#include "bst.h"


int main(){

	string command;

    while(cin >> command){
		if(command == "countSum"){

			int size;
			cin >> size;
			BST numbers;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				//cout << x << endl;
				numbers.insert(x);
			}
			//numbers.print_inorder();
			int res = numbers.countSum();
			cout << "Total nodes with equal sums: " << res << endl;
		}else if(command == "previous"){
			int size;
			int val;
			cin >> size >> val;
			BST numbers;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				//cout << x << endl;
				numbers.insert(x);
			}
			int prev = numbers.previous(val);
			cout << "Previous of node " << val << " is " << prev << endl;
		}
		else{
			cerr << "ERROR: the command " << command << " is not found." << endl;
		}
    }//while


    return 0;

}//main()
