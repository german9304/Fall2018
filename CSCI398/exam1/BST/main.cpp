#include <stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

#include "bst.h"


int main(int argc, char* argv[]){

	
    BST numbers;
	string command;
	while(cin >> command){//
		if(command == "print_inorder"){
			numbers.print_inorder();
			cout << endl;
		}else if(command == "insert"){
			string word;
			cin >> word;
			int len ;
			cin >> len;
			string akey = word.substr(0, len);
			numbers.insert(akey, word);
        }else if(command == "remove"){
			string akey;
			cin >> akey;
			numbers.remove(akey);
		}else if(command == "printPath"){
			int k;
			cin >> k;
			numbers.printPath(k);
		}else{
			cerr << "ERROR: command " << command << " is not found." << endl;
		}
	}//while

    return 0;

}//main()
