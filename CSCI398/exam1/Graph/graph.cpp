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
		cout << u << ": ";
		for(int i = 0; i < uSize; i++)
			cout << Adj[u][i].neighbor << " ";
		cout <<endl;
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

void Graph::backTrack(vector<int> & parents, int u, int v, int vertex, bool & found){
     if(u == vertex){
     	 found = true;
     }
     if(u == parents[u]){
     return;
     }
   u = parents[u];
   backTrack(parents,u, v, vertex,found);
}
void Graph::dfsVisitCycle(int s, int u, int vertex, bool & found, int & lastv){
	colors[u] = 'G';
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			int w = Adj[u][i].w;
			if(w!= -1){
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisitCycle(s, v, vertex, found, lastv);
			}
			if(colors[v] == 'G'  && s == v){
               backTrack(parents,u, v, vertex, found);
                 if(found){
                   found = true;
                   lastv = u;
                }
			}
		}
	}//for
}//dfsVisit	
void  Graph::dfsMarkNodes(vector<int> & parents,int u, int v){
    if(u == v){
     return;
     }
   int ch = u;
   int p = v;
   for(int i = 0; i < (int)Adj[p].size(); i++){
			int vch = Adj[p][i].neighbor;
			if(vch == ch){
               Adj[p][i].w = -1;
			}
   }
   u = v;
   v = parents[v];
   dfsMarkNodes(parents,u, v);


}
//Problem 3
bool Graph::foundCycle(int u, int v){
	bool found = false;
	int lastv = 0;
	dfsVisitCycle(u, u, v, found, lastv);
	if(found){
		dfsMarkNodes(parents, u, lastv);
		for(int i = 0; i < size; i++){
			parents[i] = i;
			colors[i] = 'W';
		}
		found = false;
		dfsVisitCycle(u, u, v, found, lastv);
		return true;
	}
	return false;
}
bool Graph::twoCycles(int u, int v){
   bool f = foundCycle(u,v);
   return f;
} 







