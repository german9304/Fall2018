#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using namespace std;

#include "graph.h"

int main(){

	int N;
	cin >> N;
	Graph ag(N);

	string command;
	while(cin >> command){
		if(command == "addEdge"){
			int u, v, w;
			cin >> u >> v >> w;
			ag.addEdge(u, v, w);
		}else if(command == "removeEdge"){
			int u, v;
			cin >> u >> v;
			ag.removeEdge(u, v);
		}else if(command == "bfs"){
			int s;
			cin >> s;
			cout << "BFS on " << s << endl;
			ag.bfs(s);
		}else if(command == "dfs"){
			cout << "DFS" << endl;
			ag.dfs();
		}
        else if(command == "printDistance"){
			cout << "Distances:" << endl;
			ag.printDistance();
		}else if(command == "printParents"){
			cout << "Parents:" << endl;
		ag.printParents();
		}else if(command == "printGraph"){
			cout << "Graph is:" << endl;
			ag.printGraph();
		}else if(command == "twoCycles"){
			cout << "Graph is:" << endl;
			ag.printGraph();
			int u, v;
			cin >> u >> v;
			bool res = ag.twoCycles(u, v);
			if(res)
				cout << "There are two distinct cycles from " << u << " to " << v << "." << endl;
			else
				cout << "There are NO two distinct cycles from " << u << " to " << v << "." << endl;
		}else{
			cerr << "ERROR: the command " << command << " is not found." << endl;
		}
	}//while
  return 0;
}
