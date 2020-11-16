#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "ugraph.h"

Ugraph::Ugraph(int N){

  size = N;

  Adj.resize(size);
  distance.resize(size);
  parents.resize(size);
  colors.resize(size);
  stamps.resize(size);

}//default

void Ugraph::addEdge(int u, int v){
  Adj[u].push_back(edge(v, 0));
  Adj[v].push_back(edge(u, 0));
}

void Ugraph::addEdge(int u, int v, int weight){
  Adj[u].push_back(edge(v, weight));
  Adj[v].push_back(edge(u, weight));
}

void Ugraph::removeEdge(int u, int v)
{
  int sizeU = (int) Adj[u].size();

  for (int i = 0; i < sizeU; i++)
  {
    int cur = Adj[u][i].neighbor;

    if (cur == v)
    {
      Adj[u][i] = Adj[u][sizeU - 1];
      Adj[u].resize(sizeU - 1);
      break;
    }
  }

  int sizeV = (int) Adj[v].size();

  for (int i = 0; i < sizeV; i++)
  {
    int cur = Adj[v][i].neighbor;

    if (cur == u)
    {
      Adj[v][i] = Adj[v][sizeV - 1];
      Adj[v].resize(sizeV - 1);
      break;
    }
  }
}

void Ugraph::printGraph(){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < (int)Adj[i].size(); j++){
      int v = Adj[i][j].neighbor;
      cout << v << " " ;
    }//for j
    cout << endl;
  }
}//printGraph

void Ugraph::bfs(int s){
  for(int i = 0; i < size; i++){
    distance[i] = INT_MAX;
    parents[i] = i;
  }//for
  distance[s] = 0;
  queue<int> aq;
  aq.push(s);
  while(!aq.empty()){
    int u = aq.front();
    cout << u << " ";
    aq.pop();

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

void Ugraph::dfs(){
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

void Ugraph::dfsVisit(int u, int &t){
  cout << u << " ";

  colors[u] = 'G';
  stamps[u].d = t;
  t++;

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

bool Ugraph::distinctPaths(int u, int v)
{
  for (int i = 0; i < (int) Adj.size(); i++)
  {
    for (int j = 0; j < (int) Adj[i].size(); j++)
    {
      Adj[i][j].w = 0;
    }
  }

  bfsPath(u);

  vector <int> pathF;
  vector <int> pathS;

  if (distance[v] != INT_MAX)
  {
    weight(v);
    paths(v, pathF);
    
    bfsPath(u);

    if (distance[v] != INT_MAX)
    {

      weight(v);
      paths(v, pathS);

      for (int i = 0; i < (int) pathF.size(); i++)
      {
        cout << pathF[i] << " ";
      }

      cout << endl;

      for (int i = 0; i < (int) pathS.size(); i++)
      {
        cout << pathS[i] << " ";
      }

      cout << endl;
      return true;
    }
  }

  return false;
}

void Ugraph::weight(int u)
{
  if (parents[u] == u)
    return;

  for (int i = 0; i < Adj[u].size(); i++)
  {
    if (Adj[u][i].neighbor == parents[u])
      Adj[u][i].w = -1;
  }

  for (int i = 0; i < Adj[parents[u]].size(); i++)
  {
    if (Adj[parents[u]][i].neighbor == u)
      Adj[parents[u]][i].w = -1;
  }

  weight(parents[u]);
}

void Ugraph::paths(int u, vector<int> &path)
{
  if (parents[u] == u)
  {
    path.push_back(u);
    return;
  }

  paths(parents[u], path);
  path.push_back(u);
}

void Ugraph::bfsPath(int s){
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

    for(int i = 0; i < (int)Adj[u].size(); i++){
      int v = Adj[u][i].neighbor;
      if((distance[v] == INT_MAX) && (Adj[u][i].w != -1))
      {
        distance[v] = distance[u] + 1;
        parents[v] = u;
        aq.push(v);
      }
    }//for
  }//while
}//bfs

void Ugraph::printBridges()
{
  dfsBridges();
}

void Ugraph::dfsBridges(){
  vector<int> low;

  for(int i = 0; i < size; i++){
    parents[i] = i;
    colors[i] = 'W';
    low.push_back(0);
  }	
  int t = 0;

  for(int i = 0; i < size; i++){
    if(colors[i] == 'W'){
      dfsVisitBridges(i, t, low);
    }//if
  }//for
}//dfs

void Ugraph::dfsVisitBridges(int u, int &t, vector<int> &low)
{
  colors[u] = 'G';
  stamps[u].d = t;
  low[u] = t;
  t++;

  for(int i = 0; i < (int)Adj[u].size(); i++)
  {
    int v = Adj[u][i].neighbor;

    if(colors[v] == 'W')
    {
      parents[v] = u;
      colors[v] = 'G';
      dfsVisitBridges(v, t, low);

      if (low[v] < low[u])
        low[u] = low[v];

      else if (low[v] == stamps[v].d)
        cout << u << " " << v << endl;
    }

    else if ((colors[v] == 'G') && (parents[u] != v))
      low[u] = min(low[u], stamps[v].d);
  }//for

  colors[u] = 'B';
  stamps[u].f = t;
  t++;
}//dfsVisit	

void Ugraph::printCC()
{
  int id = 0;
  vector<int> ids;
  ids.resize(size);

  dfsCC(id, ids);

  vector< vector<int> > difCC;
  difCC.resize(id);

  for (int i = 0; i < id; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (i == ids[j])
        difCC[i].push_back(j);
    }
  }

  for (int i = 0; i < (int) difCC.size(); i++)
  {
    for (int j = 0; j < (int) difCC[i].size(); j++)
    {
      cout << difCC[i][j] << " ";
    }
    cout << endl;
  }
}

void Ugraph::dfsCC(int &id, vector<int> &ids){
  for(int i = 0; i < size; i++){
    parents[i] = i;
    colors[i] = 'W';
  }	
  int t = 0;

  for(int i = 0; i < size; i++)
  {
    if(colors[i] == 'W'){
      dfsVisitCC(i, t, id, ids);
      id++;
    }//if
  }//for
}//dfs

void Ugraph::dfsVisitCC(int u, int &t, int &id, vector<int> &ids){

  colors[u] = 'G';
  stamps[u].d = t;
  ids[u] = id;
  t++;

  for(int i = 0; i < (int)Adj[u].size(); i++)
  {
    int v = Adj[u][i].neighbor;

    if(colors[v] == 'W'){
      parents[v] = u;
      colors[v] = 'G';
      ids[v] = id;
      dfsVisitCC(v, t, id, ids);
    }
  }//for

  colors[u] = 'B';
  stamps[u].f = t;
  t++;
}//dfsVisit	

bool Ugraph::twoColoring()
{
  vector<char> c(size, 'R');

  dfsColoring(c);
  
  for (int i = 1; i < (int) c.size(); i++)
  {
    if (c[i - 1] == c[i])
      return true;
  }

  return false;
}

void Ugraph::dfsColoring(vector<char> &c){

  for(int i = 0; i < size; i++){
    parents[i] = i;
    colors[i] = 'W';
    c[i] = 'W';
  }	

  int t = 0;

  for(int i = 0; i < size; i++){
    if(colors[i] == 'W'){
      dfsVisitColoring(i, t, c);
    }//if
  }//for
}//dfs

void Ugraph::dfsVisitColoring(int u, int &t, vector<char> &c){
  colors[u] = 'G';
  stamps[u].d = t;
  t++;

  for(int i = 0; i < (int)Adj[u].size(); i++){
    int v = Adj[u][i].neighbor;
    if(colors[v] == 'W'){
      parents[v] = u;
      colors[v] = 'G';
      if (c[v-1] == 'B')
        c[v] = 'R';
      else
        c[v] = 'B';
      dfsVisitColoring(v, t, c);
    }
  }//for
  colors[u] = 'B';
  stamps[u].f = t;
  t++;
}//dfsVisit	
