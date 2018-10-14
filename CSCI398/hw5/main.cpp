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
void leftRec(int left){
   if(left == 0){
     return;
   }
   cout << "res before: "<< left <<endl;
    int res = left/2;
   leftRec(res);
   leftRec(res);
   cout << "res after: "<< left <<endl;
}
void rightRec(int right, int bits){
   if(bits == 0){
     return;
   }
   // cout << "res before: "<< bits <<endl;
   int res = bits/2;
   lefttRec(res);
   // cout << "res after: "<< bits <<endl;
}
int countOnes(unsigned int _ui, int bits){
 if(length == 1){
//    int res  = getBit(ui, 1);
//    cout <<"ui: " <<  ui <<endl;
    return ui;
  }
//  cout << "length: " << length <<endl;
  unsigned int ld = length/2;
  unsigned int lres = ui >> ld;
  int leftBits = countOnes(lres, ld);
//  cout << "ll: " <<leftBits <<endl;
//  cout << "ll: " <<lres <<" " <<  ui <<" " <<  length <<endl;
  unsigned int res =  ui << ld;
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

