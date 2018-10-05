#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;

#include "list.h"


int main(){
    List alist;
	int size1;
	cin >> size1;
	int k;
	cin >> k;
	int i = 0;
	while(i++ < size1){
		int x;
		cin >> x;
		alist.insert(x);
	}
	cout << "The list is:" << endl;
	alist.print();
	cout << "Alternating values backward starting with " << k << "-th node:" << endl;
	alist.printAlternate(k);

return 0;
}//main()
