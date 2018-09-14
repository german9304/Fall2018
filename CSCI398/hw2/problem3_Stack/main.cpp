#include<iostream>
#include<string>
#include <stack> 
using namespace std;

bool is_balanced(string & str, stack<char> astack){
	bool balanced = true;
	for(unsigned int i = 0;i < str.length(); i++){
		if(str[i] == '('){
			astack.push(str[i]);
		}else{
			if(astack.empty()){
				balanced = false;
			}else{
				astack.pop();
			}
		}
	}
	if(astack.empty() && balanced){
		return true;
	}else{
		return false;
	}
}



int main(){
	std::stack<char> astack;
	string str;
	cin>>str;
	bool is = is_balanced(str, astack);
	if(is){
		cout << "True." <<endl;
	}else{
		cout << "False." <<endl;
	}
	return 0;
}