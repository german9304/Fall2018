#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "graph.h"


Graph::Graph(int n){
	size = n;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);
	transpose.resize(size);

	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
		colors[i] = 'W';
	}//for
}//constructor

void Graph::addEdge(int u, int v, int aweight){

	Adj[u].push_back(edge(u, v, aweight));

}

void Graph::removeEdge(int u, int v){
	int uSize = (int)Adj[u].size();


	for(int i = 0; i < uSize; i++){
		int child = Adj[u][i].neighbor;
		if(child == v){
			Adj[u][i].neighbor = Adj[u][uSize-1].neighbor;
			Adj[u][i].w = Adj[u][uSize-1].w;
			Adj[u].resize(uSize - 1);
			break;
		}
	}//for
	
}//removeEdge

void Graph::printGraph(){
	for(int u = 0; u < size; u++){
		int uSize = (int)Adj[u].size();
		for(int i = 0; i < uSize; i++)
			cout << Adj[u][i].neighbor << " " ;
		cout << endl;
	}
}

void Graph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
        cout << u << " ";
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;

				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	cout << endl;
}//bfs

void Graph::dfs(){
	distanceDFS.resize(size, INT_MAX);
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			dfsVisit(i, t);
		}//if
	}//for
	cout << endl;
}//dfs

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	

void Graph::dfs_longest(int & from, int & to){
	// cout << "size: " <<size <<endl;
	 // vector<int> distanceArray(size,INT_MAX);
	distanceDFS.resize(size, INT_MAX);
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}
	// cout << "distance array " <<endl;
	// for(int i = 0; i < size; i++){
	// 	cout << distanceDFS[i] <<endl;
	// }		
	int t = 0;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			distance[i] = 0;
			dfsVisit_longest(i, t, from, to);
		}//if
	}//for
	// cout << "distance array " <<endl;
	// for(int i = 0; i < size; i++){
	// 	cout << distanceDFS[i] <<" ";
	// }
	// cout << "max: " <<max_distance <<endl;	
	// cout << endl;
}//dfs

void Graph::dfsVisit_longest(int u, int &t, int & from, int & to){
	// int sum =  0;
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	// cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			// sum++;
			if(colors[v] == 'W'){
				parents[v] = u;
				distance[v] = distance[u] + 1;
				colors[v] = 'G';
				dfsVisit_longest(v, t, from, to);
			}
			// cout << "u's: " << u << endl;
			if(colors[v] == 'G'){
			   // cout <<endl;
				int val = (distance[u] - distance[v]) + 1;
				if(val > max_distance){
					from = u; 
					to = v;
					max_distance = val;
				}
			   // cout << "distance u: " << distanceDFS[u] << " distance v: " << distanceDFS[v] <<endl;
	           // cout <<"u: " << u <<  " v: " << v << endl;
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	


void Graph::retrieve_longestlist(vector< int >  distance, int from, int to){
     if(from == to){
        return;
     }
     from = parents[from];
     retrieve_longestlist(distance,from,to);
      cout << from<<" ";
}
int Graph::longestCycle(){
	int from, to = 0;
	dfs_longest(from, to);
	// bfs(0);
	 retrieve_longestlist(distance, from , to);
	 cout << from <<" " <<  to << " " <<endl;
     return max_distance;
}

void Graph::allToOnePaths(){

}





