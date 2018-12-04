
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<algorithm>

using namespace std;

int max(int a, int b); 
   
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(vector<vector<int>> & l_w, string a, string b, int m, int n ) 
{ 
   // int L[m+1][n+1]; 
   
   
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note  
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (int i=0; i<=m; i++) 
   { 
     for (int j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0){
         l_w[i][j] = 0; 
       }else if (a[i-1] == b[j-1]) {
         l_w[i][j] = l_w[i-1][j-1] + 1; 
       }
       else{
         l_w[i][j] = max(l_w[i-1][j], l_w[i][j-1]); 
       }
     } 
   } 
     
   return l_w[m][n];
} 
   
string print_lcs(
  vector<vector<int>> & l_w, 
  int index, 
  string a, 
  string b, 
  int m, 
  int n){

  vector <char> l_c_s(index);
  string res;
  int i = m, j = n; 
  while (i > 0 && j > 0) 
  { 
    if (a[i-1] == b[j-1]) 
    { 
      l_c_s[index-1] = a[i-1]; // Put current character in result 
      i--; j--; index--;     // reduce values of i, j and index 
      }else if (l_w[i-1][j] > l_w[i][j-1]){
         i--;
      }else{
         j--;
      } 
   }
   for (int i = 0; i < (int) l_c_s.size(); ++i)
    {
      res += l_c_s[i];
    } 
    return res;
}
/* Utility function to get max of 2 integers */
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
   
/* Driver program to test above function */
int main() 
{ 
  // char X[] = "AGGTAB"; 
  // char Y[] = "GXTXAYB"; 
  string a;
  string b;
  cin >>a;
  cin >>b;
  // printf("strings\n");
  // cout << a << " " << b <<endl;
  int a_l = a.length();
  int b_l = b.length();
  // printf("lengths\n");
  // cout << a_l << " " << b_l <<endl;
  // int m = strlen(X); 
  // int n = strlen(Y); 
  vector<vector<int>> l_w(a_l + 1, vector<int> (b_l + 1, 0)); 
  int r = lcs(l_w, a, b, a_l, b_l); 
  if(r){
    string res = print_lcs(l_w, r, a, b, a_l, b_l);
    cout << "LCS: " << res <<endl;
    cout << "Length: " << r <<endl;
  }else{
    cout << "LCS: " <<endl;
    cout << "No LCS was found." <<endl;
  }
  // printf("Length of LCS is %d", lcs( X, Y, m, n ) ); 
  
  return 0; 
} 