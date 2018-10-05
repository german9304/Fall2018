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
		for(int i = 0; i < uSize; i++){
			cout << Adj[u][i].neighbor << " " << " w: " << Adj[u][i].w <<" ";
		cout <<endl;
	    }
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
     if(u == v){
     	 cout <<"test found: " <<v << " " <<  u <<" ";
     	 found = true;
   	 // return;
     }
     if(u == parents[u]){
     	 // cout << "test not found" <<endl;
     return;
     }
       // cout <<"backTrack: " <<  u <<" ";
      // cout <<"backTrack: " <<u << " " <<  parents[u] <<" ";
   u = parents[u];
   backTrack(parents,u, v, vertex,found);
    // cout << u <<" ";
}
void Graph::dfsVisitCycle(int u, int vertex, bool & found, int & lastv){
	colors[u] = 'G';
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			int w = Adj[u][i].w;
			// cout <<w <<  "vertex: " << vertex << " " << v << endl;
			if(w!= -1){
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisitCycle(v, vertex, found, lastv);
			}
			if(colors[v] == 'G' && !found){
				 cout <<endl;
				  cout <<" u "<< u  << " v: " << v << endl;
				  cout << "parents: " <<endl;
		    for(int i = 0; i < size; i++){
					cout << parents[i] <<" ";

			}
             // cout <<endl;
			 if(u == vertex){
			 	  cout << "found: " <<endl;
			//  	   for(int i = 0; i < size; i++){
			// 		cout << parents[i] <<" ";

			// }
			// cout <<endl;
			 	 lastv = u;
			 	 found = true;
			 }else{
               backTrack(parents,u, v, vertex, found);
                if(found){
                  found = true;
                  lastv = u;
                }
			 }
			}
		}
	}//for
}//dfsVisit	
void  Graph::dfsMarkNodes(vector<int> & parents,int u, int v){
    if(u == v){
     return;
     }
    cout << "iter v: " << v  << " parent: " << parents[v] << endl;
   int p = parents[v];
   int ch = v;
   for(int i = 0; i < (int)Adj[p].size(); i++){
			int vch = Adj[p][i].neighbor;
			if(vch == ch){
               Adj[p][i].w = -1;
			}
   }
   v = parents[v];
   dfsMarkNodes(parents,u, v);


}
//Problem 3
bool Graph::foundCycle(int u, int v){
	  bool found = false;
        // while(!found){
	  int lastv = 0;
          dfsVisitCycle(u, v, found, lastv);
        // }
         // cout << "after while parents" <<endl;
        // for(int i = 0; i < size ; i++){
        //       	cout << parents[i] <<" ";
        // }

          if(found){
          	// cout << "lastv: " << lastv <<endl;
			dfsMarkNodes(parents, u, lastv);
			 for(int i = 0; i < size; i++){
					parents[i] = i;
					colors[i] = 'W';
			}
			found = false;
			  printGraph();
			dfsVisitCycle(u, v, found, lastv);
             // printGraph();
            cout << "found: " << found << endl;
          }

       return true;
}
bool Graph::twoCycles(int u, int v){
   bool f = foundCycle(u,v);
   f = true;
   return true;
} 







