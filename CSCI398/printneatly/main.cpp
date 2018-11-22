#include <iostream>
#include<climits>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;

//////////////////////////////////////////
void print2(int k, int i, int j,vector<string> l){
    for(i;i<=j;i++){
      cout << " " << l[i];
    }
    cout << endl;
}

int print1(int p[],int j,vector<string> l){ //p={0,1,1,2,2,5} t03
  int k=0;
  int i=p[j];
  cout << i << " " << j << endl;
  if(i==0){
    k=0;
  }
  else{
    k=print1(p,i-1,l)+1;
  }
  //cout<<"Calling print2: k="<<k<<", i="<<i<<", j="<<j<<endl;
  print2(k,i,j,l);
  return k;
}
///////////////////////////////////////////

// l = total string
// n = number of words
// M = max line width
void printNeatly(vector<string> l,int n,int M){
  int extras[n][n];
  int lc[n][n];
  int c[n+1];
  int p[n+1];
  for(int i=0;i<n+2;i++)
    p[i]=0;//initialize p so junk doesnt appear
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      extras[i][j]=0;
      lc[i][j]=0;
    }
  }
  //extras
  for(int i=0;i<n;i++){
    extras[i][i]= M-l[i].length();
    for(int j=i+1;j<n;j++){
      extras[i][j]= extras[i][j-1]-l[j].length()-1;
    }
  }
  //lc
  for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
      if(extras[i][j]<0)
        lc[i][j]=INT_MAX;
      else if(j==(n-1) && extras[i][j]>=0)
        lc[i][j]=0;
      else
        lc[i][j] = extras[i][j]*extras[i][j];
    }
  }
  //c & p
  c[0]=0;
  for(int j=1;j<n+1;j++){
    c[j]=INT_MAX;
    for(int i=1;i<=j;i++){
      if((c[i-1]+lc[i][j])< c[j]){
        c[j]=c[i-1]+lc[i][j];
        p[j]=i;
      }
    }
  }

  //print extras
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout << extras[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
  cout << endl;
  //print lc
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout << lc[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
  cout << "N:"<<n<<endl;
  
  //print our string
  cout << "Printing l" << endl;
  for(int i=0; i<n;i++){
    cout << l[i] << " ";
  }
  cout << endl;
  //print p
  for(int i=0;i<n+1;i++)
    cout << p[i] << " ";
  cout << endl;
 
  //call print 
  int g = print1(p,n,l);
}





int numwords(string text){
  int words = 1;
  for(int i = 0;i<text.length();i++){
    if(text[i]==' ')
      words++;
  }
  return words;
}
string getword(string text, int num){
  int word =0;
  string s = "";
  for(int i=0; i<text.length();i++){
    if(text[i]==' '){
      word++;
      if(word==num)
        return s;
      s="";
    }else
    s = s + text[i];
    
  }
}

int main(){
  string text;
  getline(cin, text);
  int n,m;
  cin >> m;
  n = numwords(text);
  //cout << n <<", "<<m<< endl;

  vector<string> l;
  for(int i=0;i<n;i++){
    l.push_back(getword(text,i+1));
    cout << l[i] << endl;
  }
  printNeatly(l,n,m);
  return 0;
}
