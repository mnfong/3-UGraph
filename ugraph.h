#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
  int neighbor; // adjacent node
  int w; //keeps auxiliary information
  edge(){
    neighbor = 0;
    w = 0;
  };
  edge(int i, int j){
    neighbor = i;
    w = j;
  };
};

class Ugraph{
  public:
    Ugraph(int N);
    void bfs(int s);
    void dfs();
    void dfsVisit(int u, int &t);
    void printGraph();
    void addEdge(int u, int v);
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);

    // Problem 1
    bool distinctPaths(int u, int v);

    // Problem 2
    void printBridges();

    // Problem 3
    void printCC();

    // Problem 4
    bool twoColoring();

  private:
    vector< vector<edge> > Adj; //adjacency lists of the graph 
    vector<int> distance; //for BFS and DFS
    vector<int> parents; //for BFS and DFS
    vector<char> colors; //for DFS
    vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    vector< vector<int> > CC;
    int size;
    void bfsPath(int s);
    void paths(int u, vector<int> &path);
    void weight(int u);
    void dfsBridges();
    void dfsVisitBridges(int u, int &t, vector<int> &low);
    void dfsCC(int &id, vector<int> &ids);
    void dfsVisitCC(int u, int &t, int &id, vector<int> &ids);
    void dfsColoring(vector<char> &c);
    void dfsVisitColoring(int u, int &t, vector <char> &c);
};

#endif
