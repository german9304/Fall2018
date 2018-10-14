#include<string>
#include<iostream>
#include<bitset>
using std::bitset;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

typedef unsigned int _ui;

int getBit(int x, int i){
  int b = x << i;
  return b & x;
}

int countOnes(unsigned int _ui, int bits){
 if(bits == 1){
//    int res  = getBit(ui, 1);
//    cout <<"ui: " <<  ui <<endl;
    return _ui;
  }
//  cout << "length: " << length <<endl;
  unsigned int ld = bits/2;
  unsigned int lres = _ui >> ld;
  int leftBits = countOnes(lres, ld);
//  cout << "ll: " <<leftBits <<endl;
//  cout << "ll: " <<lres <<" " <<  ui <<" " <<  length <<endl;
  unsigned int res =  _ui << ld;
  unsigned int sh  = 0;
  unsigned int num = 0;
  if(ld < 16){
    sh =  (1<< (ld*2))-1;
    num = (res & sh) >> ld;
  }else{
//    cout <<"res inside: " << res <<endl;
     num =  res >> 16;
  }

//  cout << ui << " " << ld << " temp: " << temp <<endl;
//  cout << "num: " << num <<endl;
//  cout << "res: " << res <<endl;
//  cout << "sh: " << sh <<endl;
  int rightBits = countOnes(num, ld);

//  int sum = 0;
//  if(leftBits){
//    sum++;
//  }
//  if(rightBits){
//    sum++;
//  }
  return rightBits + leftBits;

}

void printDif(unsigned int _ui,unsigned int y){

}

void flipTwo(unsigned int _ui){

}
int main(){

	string command;
	while(cin >> command){
		if(command == "countOnes"){
			_ui x;
			cin >> x;
			int res = countOnes(x, 32);
			cout << "Total 1s in " << x << endl;
			bitset<32> b(x);
			cout << b << endl;
			cout << res << endl;
		}else if(command == "printDif"){
			_ui x, y;
			cin >> x >> y;
            bitset<32> xb(x);
            bitset<32> yb(y);
			cout << "Total different odd bits, even bits and tuples in " << x << " and " << y << ":" << endl;
			cout << xb << endl << yb << endl;
			printDif(x, y);
		}else if(command == "flipTwo"){
			_ui x;
			cin >> x;
			bitset<32> xb(x);
			cout << "Indices of two flipped zeros and the longest run of ones for integer " << x << endl;
			cout << xb << endl;
			flipTwo(x);
		}else{
			cerr << "ERROR: the command " << command << " is not found." << endl;
		}
	}//while
	return 0;
}//main

