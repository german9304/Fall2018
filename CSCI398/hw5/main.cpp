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

int getBit(unsigned  int ui, int length){
  return ui & (1<<length);
}

int countOnes(unsigned int _ui, int bits){
 if(bits == 1){
    return _ui;
  }
  unsigned int ld = bits/2;
  unsigned int lres = _ui >> ld;
  int leftBits = countOnes(lres, ld);
  unsigned int res =  _ui << ld;
  unsigned int sh  = 0;
  unsigned int num = 0;
  if(ld < 16){
    sh =  (1<< (ld*2))-1;
    num = (res & sh) >> ld;
  }else{
     num =  res >> 16;
  }
  int rightBits = countOnes(num, ld);
  return rightBits + leftBits;

}

void oddsEvens(unsigned int _ui,unsigned int &evens,unsigned int &odds){
  for(unsigned int i = 0; i < 32; i++){
    unsigned int bit = getBit(_ui, i);
    if(i%2 == 0){
      evens+= bit;
    }else{
      odds+= bit;
    }
  }
}

int tuples(unsigned int _ui,unsigned int y){
  unsigned int num_1 = 0;
  unsigned int num_2 = 0;
  unsigned int total_sum = 0;
  for(int i = 0; i < 32; i++){
    unsigned int res_1 = getBit(_ui,i);
    unsigned int res_2 = getBit(y,i);
    num_1+=res_2;
    num_2+=res_1;
    if(i % 2 == 1){
    unsigned int res = num_2 ^ num_1;
      if(res){
        total_sum++;
      }
      num_1 = 0;
      num_2 = 0;
    }
  }
  return total_sum;
}

void printDif(unsigned int _ui,unsigned int y){
  unsigned odds_1 = 0;
  unsigned int evens_1 = 0;
  unsigned int odds_2 = 0;
  unsigned int evens_2 = 0;
  oddsEvens(_ui,evens_1,odds_1);
  oddsEvens(y,evens_2,odds_2);
  unsigned int evenRes= evens_1 ^ evens_2;
  unsigned int oddRes = odds_1 ^ odds_2;
  int onesOdd = countOnes(oddRes, 32);
  int onesEven = countOnes(evenRes, 32);
  int totalTuples = tuples(_ui, y);
  cout <<onesOdd << " " << onesEven  << " " <<totalTuples << endl;
}

void flipTwo(unsigned int _ui){
  vector<int> bits;
  for(int i = 0; i < 32; i++){
    unsigned int bit = getBit(_ui, i);
//    cout << bit << " ";
    if(!bit){
      bits.push_back(i);
    }
  }
//  cout <<endl;
//  for(int i = 0; i < bits.size();i++){
//    cout << bits[i] << " ";
//  }
//  cout <<endl;
  int max = -1;
  int iter = 0;
  int cursum = 0;
  int index_1 = 0;
  int index_2 = 0;
  if(bits.size() && bits.size() > 1){
  for(int i = 0; i < 32; i++){
     if(bits[iter] == i && iter < bits.size()){
       //cout <<iter<< " ";
      if(iter == 2){
//        cout << i << " "<<iter << endl;
//        break;
        cursum = i;
        if(i > max){
          max = i;
         // cout <<bits[iter-1] << " " << bits[iter-2] << " " << max << endl;
          index_1 = bits[iter-2];
          index_2 = bits[iter-1];
        }
      //cout << i << " "<<cursum<< " " << iter << endl;
      }else if(iter > 2){
        //cout << max << " " << iter << " " << i << endl;
        int s =(i-1) - (bits[iter-3]);
      //  cout <<i << " " << "sum: " <<  s << " " << iter << " " << bits[iter-3] << endl;
        if(s > max){
          max = s;
          index_1 = bits[iter-2];
          index_2 = bits[iter-1];
        //  cout << max << " s: " << s << " " << i << endl;
        }
       // break;
      }
      iter++;
    }
  }
  }
if(bits.size() && bits.size() > 1){
  int lastSum = (31-bits[iter-3]);
  if(lastSum > max){
    //cout <<bits[iter-1] << " s: " << bits[iter-2] << " " << max << endl;
    cout << "true" <<endl;
    max = lastSum;
    index_1 = bits[iter-2];
    index_2 = bits[iter-1];
    }
   }
  if(bits.size() == 1){
    index_1 = bits[0];
    index_2 = -1;
    max = 32;
  }
  if(!bits.size()){
    index_1 = -1;
    index_2 = -1;
    max = 32;
  }
  cout <<index_1 << " " << index_2 << " " << max <<endl;
//  cout <<endl;
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

