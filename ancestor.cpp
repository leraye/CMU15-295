#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

class Ancestor{
  int N;
  int K;
  vector<vector<int>> ancestor;
  vector<int> level;
  vector<int> parent;
  void construct_parent(unordered_map<int, unordered_set<int>>& graph){
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
  void preprocess(unordered_map<int, unordered_set<int>>& graph){
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
public:
  Ancestor(int n, unordered_map<int, unordered_set<int>>& graph){
    N = n;
    K = (int)ceil(log2(n));
    level.resize(n + 1, 0);
    parent.resize(n + 1, 0);
    for(int i = 0; i <= n; ++i){
      vector<int> row(K + 1, 0);
      ancestor.push_back(row);
    }
    preprocess(graph);
  };
  bool isAncestor(int u, int v){
    if(u == v)
      return true;
    if(level[u] >= level[v])
      return false;
    int l = K;
    while(l >= 0 && (1 << l) > level[v] - level[u])
      --l;
    return isAncestor(u, ancestor[v][l]);
  };
};

int main(){
  int n, q;
  cin >> n >> q;
  unordered_map<int, unordered_set<int>> g;
  int u, v;
  for(int i = 1; i < n; ++i){
    cin >> u >> v;
    g[u].insert(v);
    g[v].insert(u);
  }
  
  auto pt = new Ancestor(n, g);
  for(int i = 0; i < q; ++i){
    cin >> u >> v;
    cout << (pt -> isAncestor(u, v) ? "YES" : "NO") << endl;
  }
  return 0;
}
