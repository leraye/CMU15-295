#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <cmath>
#include <utility>

using namespace std;

class Ancestor{
  int N;
  int K;
  vector<vector<int>> ancestor;
  vector<int> level;
  vector<int> parent;
  void construct_parent(unordered_map<int, vector<int>>& graph){
    deque<int> q;
    q.push_back(1);
    parent[1] = -1;
    while(!q.empty()){
      int node = q.front();
      q.pop_front();
      for(int nxt : graph[node]){
	if(parent[nxt] == 0){
	  parent[nxt] = node;
	  q.push_back(nxt);
	  level[nxt] = level[node] + 1;
	}
      }
    }
  };
  void preprocess(unordered_map<int, vector<int>>& graph){
    construct_parent(graph);
    for(int i = 1; i <= N; ++i){
      ancestor[i][0] = parent[i];
    }
    for(int k = 1; k <= K; ++k){
      for(int i = 1; i <= N; ++i){
	if(ancestor[i][k - 1] != -1){
	  ancestor[i][k] = ancestor[ancestor[i][k - 1]][k - 1];
	}
      }
    }
  };
  int LCA(int u, int v){
    if(level[u] > level[v])
      swap(u, v);
    int l;
    if(level[v] > level[u]){
      l = K;
      while(l >= 0){
	if((1 << l) <= level[v] - level[u]){
	  v = ancestor[v][l];
	}
	--l;
      }
    }
    if(u == v)
      return u;
    l = K;
    while(l >= 0){
      if(ancestor[u][l] != ancestor[v][l]){
	u = ancestor[u][l];
	v = ancestor[v][l];
      }
      --l;
    }
    return parent[u];
  };
public:
  Ancestor(int n, unordered_map<int, vector<int>>& graph){
    N = n;
    K = (int)ceil(log2(n));
    level.resize(n + 1, 0);
    parent.resize(n + 1, 0);
    for(int i = 0; i <= n; ++i){
      vector<int> row(K + 1, -1);
      ancestor.push_back(row);
    }
    preprocess(graph);
  };
  int min_dist(int u, int v, int w){
    int p1 = LCA(u, v);
    int p2 = LCA(u, w);
    int p3 = LCA(v, w);
    int q1 = level[u] - level[p1] + level[v] - level[p1];
    int q2 = level[u] - level[p2] +  level[w] - level[p2];
    int q3 = level[v] - level[p3] + level[w] - level[p3];
    int h1 = LCA(p1, w);
    int h2 = LCA(p2, v);
    int h3 = LCA(p3, u);
    q1 += level[p1] - level[h1] + level[w] - level[h1];
    q2 += level[p2] - level[h2] + level[v] - level[h2];
    q3 += level[p3] - level[h3] + level[u] - level[h3];
    return min(q3, min(q1, q2));
  }
};

int main(){
  int n, q;
  cin >> n >> q;
  int u, v;
  unordered_map<int, vector<int>> g;
  for(int i = 1; i < n; ++i){
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  auto pt = new Ancestor(n, g);
  g.clear();
  int w;
  for(int i = 0; i < q; ++i){
    cin >> u >> v >> w;
    cout << pt -> min_dist(u, v, w) << endl;
  }
  return 0;
}
