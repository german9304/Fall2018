#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;


vector<int>  printNeatly (vector<int> l, int n, int M)
{

  int extras[n+1][n+1];
  

  int lc[n+1][n+1];
  

  int c[n+1];
  

  vector<int> p(n+1);
  
  int i, j;
  

  for (i = 1; i <= n; i++)
  {
    extras[i][i] = M - l[i-1];
    for (j = i+1; j <= n; j++)
      extras[i][j] = extras[i][j-1] - l[j-1] - 1;
  }
  

  for (i = 1; i <= n; i++)
  {
    for (j = i; j <= n; j++)
    {
      if (extras[i][j] < 0)
        lc[i][j] = INT_MAX;
      else if (j == n && extras[i][j] >= 0)
        lc[i][j] = 0;
      else
        lc[i][j] = extras[i][j]*extras[i][j];
    }
  }
  

  c[0] = 0;
  for (j = 1; j <= n; j++)
  {
    c[j] = INT_MAX;
    for (i = 1; i <= j; i++)
    {
      if (c[i-1] != INT_MAX && lc[i][j] != INT_MAX && (c[i-1] + lc[i][j] < c[j]))
      {
        c[j] = c[i-1] + lc[i][j];
        p[j] = i;
      }
    }
  }
  return p;
}

int printSolution (vector<string> words, vector<int> p, int n)
{
  int k;
  if (p[n] == 1)
    k = 1;
  else
    k = printSolution (words, p, p[n]-1) + 1;
  for(int i = p[n]-1; i < n; i++){
    cout <<words[i] << " ";
  }
  cout <<endl;
  return k;
}

vector<string> splitText(string text){
  vector<string> av;
  string as;
  text += " ";
  for(int i = 0; i < (int) text.length(); i++){
    if(text[i] != ' '){
      as += text[i];
    }else{
      av.push_back(as);
      as = "";
    }
  }
  return av;
}
vector<int> wordLen(vector<string> words){
  vector<int> aw;
  for(int i = 0; i < (int) words.size(); i++){
    int wl = (int) words[i].length();
    aw.push_back(wl);
  }
  return aw;
}

int main(){
  string text;
  getline(cin, text);
  int M;
  cin >> M;
  cout << text <<endl;
  cout << M <<endl;
  vector<string> words = splitText(text);
  vector<int> wordsLen = wordLen(words);
  int n = (int) words.size();
  vector<int> solWords = printNeatly (wordsLen, n, M);
  printSolution(words, solWords, n);
  return 0;
}
