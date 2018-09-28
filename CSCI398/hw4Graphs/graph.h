#include<string>
#include<iostream>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class TimeStamp{
public:
    TimeStamp(): d(0), f(0){};
    int d; //discovery time
    int f; //finish time

};

struct edge{
	int source;//edge is from this node to neighbor
	int neighbor; // adjacent node
	int w; //keeps auxiliary information
	edge(){
		source = 0;
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		source = 0;//dummy value
		neighbor = i;
		w = j;
	};
	edge(int from, int to, int aweight){
		source = from;//edge is from this node
		neighbor = to;//edge is to this node
		w = aweight;//weight of this edge
	};
	
};

class Graph{
public:
	Graph(int N);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	void printGraph();
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void dfs_longest(int & from, int & to);
	void dfsVisit_longest(int u, int &t, int & from, int & to);
	void dfsTopSort();
	void dfsVisitTopSort(int u, int &t, bool & exist);
    int longestCycle();
    void allToOnePaths();
	void printDistance(){
		for(int i = 0; i < size; i++)
			cout << distance[i] << " " ;
		cout << endl;
	}
	void printParents(){
		for(int i = 0; i < size; i++){
			cout << parents[i] << " " ;
		}
		cout << endl;
	}
	void retrieve_longestlist(vector< int >  distance, int from, int to);

	
private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector< int > distance; //for BFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector< int > distanceDFS; //for DFS
	vector<TimeStamp> stamps; //for DFS
	int max_distance = -1;
    int size;
	vector<vector<edge> > transpose;
	vector<int> topsort;
};

#endif
