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

void Graph::addEdgeT(int u, int v){

	AdjT[v].push_back(edge(v, u,0));

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
	// cout << endl;
}//dfs

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	//cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
	}//for
	topsort.push_back(u);
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	

void Graph::dfs_longest(int & from, int & to){
	distanceDFS.resize(size, INT_MAX);
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}		
	int t = 0;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			distance[i] = 0;
			dfsVisit_longest(i, t, from, to);
		}//if
	}//for
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

void Graph::dfsTopSort(){
	distanceDFS.resize(size, INT_MAX);
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;
	for(int i = size-1; i > 0; i--){
		int v = topsort[i];
		bool exist = false;
	     if(colors[v] == 'W'){
			//color[i] = 'G';
			dfsVisitTopSort(v, t, exist);
			  if(!exist){
    	         cout << "does not exist" <<endl;
               }
	 	}//if
		for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	    }

	  }
	cout << endl;
}//dfs

void Graph::dfsVisitTopSort(int u, int &t, bool & exist){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	   cout  << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				// cout  << v << endl;
				if(v == topsort[0]){
                   // cout << "equal: "<< v << endl;
                   exist = true;
				}
				dfsVisitTopSort(v, t, exist);
			 }

	}//for
	// cout << "------"<<endl;
	 // colors[u] = 'B';
	stamps[u].f = t;
	t++;
	
}//dfsVisit	

void Graph::transposeGraph(){
	AdjT.resize(size);
    for(unsigned int i = 0; i < Adj.size(); i++){
    	for(unsigned int j = 0; j < Adj[i].size(); j++){
           int n = Adj[i][j].neighbor;
           addEdgeT(i, n);
    	}
    }
}
void Graph::tbfs(int s){
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
        // cout << u << " ";
		for(int i = 0; i < (int)AdjT[u].size(); i++){
			int v = AdjT[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;

				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	// cout << endl;
}
void Graph::backtrack(int s, int to, vector<int> parents){
   if(to == s){
   	 cout << to << " ";
     return;
   }

   cout << to << " ";
   to = parents[to];
   backtrack(s,to, parents);
}
void Graph::allToOnePaths(){
    dfs();
    transposeGraph();
    int s = topsort[0];
    tbfs(s);
    bool source = false;
    for(int i = 0; i < size;i++ ){
     if(distance[i] == INT_MAX){
       source = true;
       break;
     }
    }
    if(!source){
         for(int i = 0; i < size;i++){
           if(i != s){
           backtrack(s, i, parents);
            cout <<endl;
           }
         }
    }
    
}






