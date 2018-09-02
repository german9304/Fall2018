#include <string>
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

bool foundStr(string &s,const string &s1,int i, bool &isOverlap){
	bool fi = true;
	bool same = true;
     for(unsigned int index = 0; index < s1.length(); index++){
              if(s[i] != s1[index]){
                  fi = false;
							}
							i++;
		 }
if(fi){
	int pos = i - 1;
   for(unsigned int in = 0; in < s1.length(); in++){
				if(s[pos] != s1[in]){
             same = false;
				}
				pos++;
   }
	 if(same){
		 isOverlap = true;
	 }
}
		 if(!fi){
			 return false;
		 }
		 return true;
}



bool replaceSubstring(string &s, const string &s1, const string &s2, int res){
	 int s1l = s1.length();
	 int s2l = s2.length();
	 int dif = 0;
	 int difresult = 0;
		 int news = 0;
		 int newls = 0;
     if(s2l > s1l){
			  dif = s2l - s1l;
			  difresult = dif * res;
        s.resize(s.length() + difresult,'-');
				news = s.length();
				newls = news-difresult-1;
		 }else{
			 news = s.length();
			 dif = s1l - s2l;
		 }
		 char lc = s1[s1l-1];
		 bool same = true;
     if(s1l > (int)s.length()){
			 return false;
		 }
     for(int i = news; i >= 0; i--){
			  same = true;
			 if(s[i] == lc){
				 /**********/
				 int element = i;
         for(int index = s1l-1; index >=0; index--){
					 if(s[element] != s1[index]){
              same = false;
					 }
					 element--;
				 }
				 if(same){
				if(s2l > s1l){
          for(int in = newls; in >= i + 1; in--){
             s[in+dif] = s[in];
					}
				  int st = s2l-1;
			   	for(int ind = i + dif; ind > element; ind--){
               s[ind] = s2[st];
							  st--;
					}
					 newls+=dif;
				 }else if(s2l < s1l){
					 for(int in = i ;in < news-1; in++){
						 s[in] = s[in+1];
					 }
					 int pos = i-1;
					 for(int ind = s2l-1; ind>=0; ind--){
							s[pos] = s2[ind];
							pos--;
					 }
				 }
				 i = element + 1;
				}
			 }
		 }//for
		 if(s1l > s2l){
			 s.resize(s.length() - res);
		 }
		 return true;
}//
bool replace(string &s, const string &s1, const string &s2)
{
    int countS1 = 0;
		int strl = (int) s.length();
		int str1l = (int) s1.length();
		bool isOverlap = false;
		for (int i = 0; i < strl; i++)
		{
      if(s[i] == s1[0]){
				bool is = foundStr(s,s1,i, isOverlap);
        if(is){
					i+=str1l-1;
					countS1++;
				}
			}
		}

   bool rs = replaceSubstring(s,s1,s2,countS1);
	 if(!rs || isOverlap){
		 return false;
	 }
	return true;
}
bool isPalindrome(string &str){
	int strl = str.length()-1;
	for(unsigned int i = 0; i < str.length(); i++){
        if(str[i] != str[strl]){
           return false;
				}
				strl--;
	}
	return true;
}
bool palindromeRotation(const string &s)
{
	string str = s;
	string tempstr = str;
	int sl = str.length()-1;
	for(unsigned int i = 0; i< str.length();i++){
		char temp = str[i];
		for(unsigned int j = 0; j< tempstr.length()-1; j++){
      tempstr[j] = tempstr[j+1];
		}
		tempstr[sl] = temp;
		cout << tempstr <<endl;
		bool is = isPalindrome(tempstr);
		if(is){
			return true;
		}
	}
	return false;
}
int minNumber(int *ptr,const int n){
	int min = ptr[0];
  for(int i =0; i < n;i++){
     if(ptr[i] < min){
       min = ptr[i];
		 }
	}
	return min;
}
int maxNumber(int *ptr,const int n){
	int max = ptr[0];
  for(int i =0; i < n;i++){
    if(ptr[i] > max){
			max = ptr[i];
		}
	}
	return max;
}
void sortInPlace(int *ptr, const int n)
{
	int min = minNumber(ptr,n);
	int max = maxNumber(ptr,n);
	int dif = (max - min)/(n-1);
	for(int i = 0;i < n;i++){
      int difr = min + (i)*dif;
			ptr[i] = difr;
	}
}

int main()
{
	string command;
	while (getline(cin, command))
	{
		if (command == "replace")
		{
			string s, s1, s2;
			getline(cin, s);
			getline(cin, s1);
			getline(cin, s2);
			bool res = replace(s, s1, s2);
			if (res)
				cout << s << endl;
			else
				cerr << "ERROR: replace has failed." << endl;
		}
		else if (command == "palindromeRotation")
		{
			string s;
			getline(cin, s);
			bool res = palindromeRotation(s);
			if (res)
			{
				cout << "The given string is a rotation of a palindrome." << endl;
			}
			else
				cout << "The given string is not a rotation of a palindrome." << endl;
		}
		else if (command == "sortInPlace")
		{
			int n;
			cin >> n;
			int *ptr = new int[n];
			for (int i = 0; i < n; i++)
			{
				cin >> ptr[i];
			}
			cin.ignore();
			sortInPlace(ptr, n);
			for (int i = 0; i < n; i++)
				cout << ptr[i] << " ";
			cout << endl;
			delete[] ptr;
		}
		else
		{
			cerr << "ERROR: the command " << command << " is not recognized." << endl;
		}
	}
	return 0;
} //main
