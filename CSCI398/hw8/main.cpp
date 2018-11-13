#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<algorithm>
//https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
using std::map;
using std::sort;
using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::cerr;
using std::pair;
using std::make_pair;


/* Standard Binary Search function*/
int binarySearch(int arr[], int low,  
                  int high, int key) 
{ 
  if (high < low) 
    return -1; 
      
  int mid = (low + high)/2; /*low + (high - low)/2;*/
  if (key == arr[mid]) 
    return mid; 
      
  if (key > arr[mid]) 
    return binarySearch(arr, (mid + 1), high, key); 
      
  // else 
    return binarySearch(arr, low, (mid -1), key); 
} 
  
/* Function to get pivot. For array 3, 4, 5, 6, 1, 2 
   it returns 3 (index of 6) */
int findPivot(int arr[], int low, int high) 
{ 
  // base cases 
  if (high < low) return -1; 
  if (high == low) return low; 
  
   int mid = (low + high)/2; /*low + (high - low)/2;*/
   if (mid < high && arr[mid] > arr[mid + 1]) 
    return mid; 
      
   if (mid > low && arr[mid] < arr[mid - 1]) 
    return (mid-1); 
      
   if (arr[low] >= arr[mid]) 
    return findPivot(arr, low, mid-1); 
      
   return findPivot(arr, mid + 1, high); 
} 
  
/* Searches an element key in a pivoted 
   sorted array arr[] of size n */
int searchRotated(int arr[], int n, int key) 
{ 
  int pivot = findPivot(arr, 0, n-1); 
  
  // If we didn't find a pivot,  
  // then array is not rotated at all 
  if (pivot == -1) 
    return binarySearch(arr, 0, n-1, key); 
  
  // If we found a pivot, then first compare with pivot 
  // and then search in two subarrays around pivot 
  if (arr[pivot] == key) 
    return pivot; 
      
  if (arr[0] <= key) 
    return binarySearch(arr, 0, pivot-1, key); 
      
    return binarySearch(arr, pivot+1, n-1, key); 
} 


class DupArray {
public:
  class Word {
  public:
    string str; 
    int index; 
  };
  vector<Word> aw;
  int size; 
};

DupArray createDupArray(vector<string> str, unsigned int size)
{
  DupArray  dupArr;
  dupArr.aw.resize(size);
  
  unsigned int i;
  for (i = 0; i < size; i++) {
    dupArr.aw[i].str = str[i];
    dupArr.aw[i].index = i;
  }
  return dupArr;
}

int compCharChar (char a, char b) { return a < b;  }

struct compStr{
  bool operator() (DupArray::Word a ,DupArray::Word b) { return (a.str < b.str);}
} myobject;

struct compIndex{
  bool operator() (int a ,int b) { return (a< b);}
} myindex;

void groupAnagrams(vector<string> wordVec, const unsigned int size)
{
  DupArray dupArray = createDupArray(wordVec, size);
  for(unsigned int i = 0; i < size; i++){
    sort(dupArray.aw[i].str.begin(), dupArray.aw[i].str.end(), compCharChar);
  }
 
 sort(dupArray.aw.begin(), dupArray.aw.end(), myobject);
  std::map<string, vector<int>> mymap;
  std::map<string, int> myMap;
  vector<string> groupsUnique;
  for(unsigned int i = 0; i < size ; i++){
  mymap[dupArray.aw[i].str].push_back(dupArray.aw[i].index);
    groupsUnique.push_back(dupArray.aw[i].str);
  }
  std::vector<string>::iterator it = std::unique (groupsUnique.begin(), groupsUnique.end());
  groupsUnique.resize(std::distance(groupsUnique.begin(), it));
  for (it=groupsUnique.begin(); it!=groupsUnique.end(); ++it){
    vector<int> words = mymap[*it];
    sort(words.begin(), words.end(), myindex);
    for(unsigned int i = 0; i < words.size(); i++){
      cout << wordVec[words[i]] << " ";
    }
    cout <<endl;
  }
  
}



int main(){
	string command;
	while(cin >> command){
		if(command == "groupAnagrams"){
			int N;
			cin >> N;
			cin.ignore();
			string line;
			vector<string> words;
			for(int i = 0; i < N; i++){
				getline(cin, line);
				words.push_back(line);
			}
			//call your function(s) to solve this problem here:
        groupAnagrams(words, N);
		}else if(command == "searchRotated"){
			int N, M;
			cin >> N >> M;
			vector<int> numbers;
			int x;
			for(int i = 0; i < N; i++)
			{
				cin >> x;
				numbers.push_back(x);
			}//for

			//call your function (or functions) to solve this problem here:
			//don't forget to output the result
		      
        }else{
			cerr << "ERROR: command " << command << " is not recognized." << endl;
			return 1;
		}//else
	}//while


	return 0;
}

