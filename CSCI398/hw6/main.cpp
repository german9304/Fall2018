#include<string>
#include<iostream>
#include <vector>
using namespace std;

void sum( string a, string b, int i_n2, unsigned int iter);
int i_n1 = 0;
vector<int> result;
int main(void){
	string a,b;
	while(cin>>a){
		cin>>b;
		//cout << "---------"<<endl;
		//cout <<"a: " << a << " b: " << b <<endl;
		int n1 = a.length();
		int n2 = b.length(); 
        int i_n2 = 0;
        result.resize(n1 + n2, 0);
		sum( a, b, i_n2, 0);
		i_n1 = 0;
		int i = result.size() - 1; 
        while (i>=0 && result[i] == 0){
              i--; 
             }
         if (i == -1) {
           cout << "0" <<endl;
          }
        while( i >=0){
           cout << result[i];
           i--;
        }
        cout <<endl;
		//cout << "---------"<<endl;
	    result.clear();
	}
	return 0;
}

void sum(string a, string b, int i_n2, unsigned int iter){
	if(iter+1 > a.length()){
     return;
	}
    iter++;
	sum(a, b, i_n2, iter);
	int n1 = a[iter-1] - '0';
	i_n2 = 0;
	int carry = 0; 
	//cout <<"i_n1: " <<  n1 <<endl;
	for(int i = b.length() - 1;  i >=0; i--){
       int n2 = b[i] - '0';
       int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
      // cout <<"sum: "<<  sum <<endl;
       carry = sum / 10;
      // cout << sum << " " << carry <<" ";
       result[i_n1 + i_n2] = sum % 10; 
      // cout <<"res: "<<  result[i_n1 + i_n2] <<endl;
       i_n2++;
	}
	//cout <<endl;
	//cout <<"i_n2: " <<  i_n2 <<endl;
	if (carry > 0) {
         result[i_n1 + i_n2] += carry;
     } 
     i_n1++; 
	// cout <<endl;
 //    cout << "res: " << mult <<endl;
 //    mult = 0;
	//cout <<endl;

}

