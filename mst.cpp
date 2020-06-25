#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <cmath>

using namespace std;

class Edge{
public:
  int src;
  int dest;
  int wt;
};

class Graph{
public:
  int V, E;
  vector<Edge> edges;
  Graph(int n, int m){
    V = n;
    E = m;
  }
  void addEdge(int u, int v, int w){
    Edge e;
    e.src = u;
    e.dest = v;
    e.wt = w;
    edges.push_back(e);
  }
};

class disjointSet{
public:
  int parent;
  int rank;
};

int find(vector<disjointSet>& arr, int i){
  if(arr[i].parent != i){
    arr[i].parent = find(arr, arr[i].parent);
  }
  return arr[i].parent;
}

void Union(vector<disjointSet>& arr, int x, int y){
  int xroot = find(arr, x);
  int yroot = find(arr, y);
  if(arr[xroot].rank < arr[yroot].rank){
    arr[xroot].parent = yroot;
  }else{
    arr[yroot].parent = xroot;
    if(arr[xroot].rank == arr[yroot].rank){
      ++arr[xroot].rank;
    }
  }
}

bool comp(const Edge l, const Edge r){
  return l.wt > r.wt;
}

vector<Edge> KruskalMST(Graph* g){
  int V = g -> V;
  vector<Edge> ret;
  int i = 0;
  sort(g -> edges.begin(), g -> edges.end(), comp);
  vector<disjointSet> arr(V + 1);
  for(int v = 1; v <= V; ++v){
    arr[v].parent = v;
    arr[v].rank = 0;
  }
  while(i < g -> E){
    Edge next_edge = g -> edges[i++];
    int x = find(arr, next_edge.src);
    int y = find(arr, next_edge.dest);
    if(x != y){
      ret.push_back(next_edge);
      Union(arr, x, y);
    }
  }
  return ret;
}

class Forest{
private:
  int n, K;
  vector<vector<int>> ancestor;
  vector<vector<int>> path_min;
  vector<int> level;
  unordered_map<int, vector<int>> AdjList;
  void adjList(Graph* g){
    for(auto e : g -> edges){
      AdjList[e.src].push_back(e.dest);
      AdjList[e.dest].push_back(e.src);
    }
  }
  void dfs(int u, int l){
    level[u] = l;
    for(int v : AdjList[u]){
      if(level[v] < 0){
	dfs(v, l + 1);
      }
    }
  }
  int LCA(int u, int v){
    if(level[u] > level[v])
      swap(u, v);
    for(int k = K - 1; k >= 0; --k){
      if(level[v] - (1 << k) >= level[u]){
	v = ancestor[v][k];
      }
    }
    if(u == v){
      return u;
    }
    for(int k = K - 1; k >= 0; --k){
      if(ancestor[u][k] != ancestor[v][k]){
	u = ancestor[u][k];
	v = ancestor[v][k];
      }
    }
    return ancestor[u][0];
  }
public:
  Forest(Graph* g){
    n = g -> V;
    K = (int)ceil(log2(n));
    level.resize(n + 1, -1);
    adjList(g);
    for(int v = 1; v <= n; ++v){
      if(level[v] < 0){
	dfs(v, 0);
      }
    }
    for(int i = 0; i <= n; ++i){
      vector<int> parent(K + 1, -1);
      ancestor.push_back(parent);
      vector<int> pmin(K + 1, numeric_limits<int>::max());
      path_min.push_back(pmin);
    }
    for(auto e : g -> edges){
      if(level[e.src] < level[e.dest]){
	ancestor[e.dest][0] = e.src;
	path_min[e.dest][0] = e.wt;
      }else{
	ancestor[e.src][0] = e.dest;
	path_min[e.src][0] = e.wt;
      }
    }
    for(int k = 1; k <= K; ++k){
      for(int i = 1; i <= n; ++i){
	if(ancestor[i][k - 1] != -1){
	  ancestor[i][k] = ancestor[ancestor[i][k - 1]][k - 1];
	  path_min[i][k] = min(path_min[i][k - 1], path_min[ancestor[i][k - 1]][k - 1]);
	}
      }
    }
  }
  int bottleNeck(int u, int v){
    int lca = LCA(u, v);
    if(lca == -1){
      return -1;
    }
    int d = numeric_limits<int>::max();
    for(int k = K - 1; k >= 0; --k){
      if(level[v] - (1 << k) >= level[lca]){
	d = min(d, path_min[v][k]);
	v = ancestor[v][k];
      }
    }
    for(int k = K - 1; k >= 0; --k){
      if(level[u] - (1 << k) >= level[lca]){
	d = min(d, path_min[u][k]);
	u = ancestor[u][k];
      }
    }
    return d;
  }
};

int main(){
  int n, m;
  cin >> n >> m;
  Graph* g = new Graph(n, m);
  int u, v, w, q;
  for(int i = 0; i < m; ++i){
    cin >> u >> v >> w;
    g -> addEdge(u, v, w);
  }
  
  auto chosen = KruskalMST(g);
  Graph* forest = new Graph(n, chosen.size());
  for(auto e : chosen){
    forest -> addEdge(e.src, e.dest, e.wt);
  }
  
  auto pt = new Forest(forest);
  cin >> q;
  for(int i = 0; i < q; ++i){
    cin >> u >> v;
    int d = pt -> bottleNeck(u, v);
    cout << d << endl;
  }
  return 0;
}
