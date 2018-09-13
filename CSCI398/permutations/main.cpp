#include <string>
#include <iostream>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void permutations(string s){
   vector<vector<string>> av;
	 string strt = "";
	 strt+=s[0];
	 vector<string> strv;
	 strv.push_back(strt);
	 av.push_back(strv);
	 cout << "char: " << av[0][0] <<endl;
	 string str = s;

	 for(unsigned int i = 1;i< s.length()-1; i++){
		 strv.clear();
      int strl = av[i-1].size();
			int strfl = strl*2;
      for(int in = 0; in < strfl;in++){
          strv[]
			}
	 }


}

int main(){
	string a = "abc";
	permutations(a);
	return 0;
}
