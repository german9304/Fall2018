#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;

#include "list.h"


int main(){
    List alist, another;
	int size1;
	cin >> size1;
	int size2;
	cin >> size2;
	int i = 0;
	while(i++ < size1){
		int x;
		cin >> x;
		alist.insert_sorted(x);
	}
	cout << "The first list:" << endl;
	alist.print();

	i = 0;
	while(i++ < size2){
		int x;
		cin >> x;
		another.insert_sorted(x);
	}
	cout << "The second list:" << endl;
	another.print();

	alist.merge(another);
    cout << "After merging the first list is:" << endl;
	alist.print();
	cout << "After merging the second list is:" << endl;
	another.print();

return 0;
}//main()
