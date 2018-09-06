#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#include "dlist.h"

int main(){
        Dlist alist;
        int size;
		cin >> size;
		int pivot;
		cin >> pivot;
		for(int i = 0; i < size; i++){
			int x;
			cin >> x;
			alist.insert(x);
		}
		cout << "The list is:" << endl;
		alist.print();
		alist.partition(pivot);
		cout << "After partition around " << pivot << ", the list is:" << endl;
		alist.print();
		cout << "After partition the list printed in the reverse order:" << endl;
		alist.print_reverse();

        return 0;
}//main()

