#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

class Graph{
public:
  int V;
  vector<vector<int>> edges;
  vector<vector<int>> people;
  Graph(int n){
    V = n;
    edges.resize(n + 1);
    people.resize(n + 1);
  }
  void addEdge(int u, int v){
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  void addPeople(int i, int p){
    people[p].push_back(i);
  }
};

class Tree{
private:
  int n, K;
  vector<vector<int>> ancestor;
  vector<int> level;
  vector<vector<vector<int>>> sets;
  void dfs(int v, int l, vector<vector<int>>& AdjList){
    level[v] = l;
    for(int u : AdjList[v]){
      if(level[u] == -1){
	dfs(u, l + 1, AdjList);
      }
    }
  }
  vector<int> merge(vector<int>& l, vector<int>& r){
    auto p1 = l.begin();
    auto p2 = r.begin();
    vector<int> ans;
    while(p1 != l.end() && p2 != r.end()){
      if(*p1 < *p2){
	ans.push_back(*p1);
	++p1;
      }else{
	ans.push_back(*p2);
	++p2;
      }
      if(ans.size() == 10){
	return ans;
      }
    }
    while(p1 != l.end()){
      ans.push_back(*p1);
      ++p1;
      if(ans.size() == 10){
	return ans;
      }
    }
    while(p2 != r.end()){
      ans.push_back(*p2);
      ++p2;
      if(ans.size() == 10){
	return ans;
      }
    }
    return ans;
  }
  
public:
  Tree(Graph* g){
    n = g -> V;
    K = (int)ceil(log2(n));
    level.resize(n + 1, -1);
    for(int i = 0; i <= n; ++i){
      vector<int> parent(K + 1, -1);
      ancestor.push_back(parent);
      vector<vector<int>> row(K + 1);
      sets.push_back(row);
    }
    dfs(1, 0, g -> edges);
    for(int i = 1; i <= n; ++i){
      for(int j : g -> edges[i]){
	if(level[i] < level[j] && ancestor[j][0] == -1){
	  ancestor[j][0] = i;
	}
      }
      sort(g -> people[i].begin(), g -> people[i].end());
      if(g -> people[i].size() > 10){
	vector<int> arr(g -> people[i].begin(), g -> people[i].begin() + 10);
	sets[i][0] = arr;
      }else{
	sets[i][0] = g -> people[i];
      }
      
    }
    for(int k = 1; k <= K; ++k){
      for(int i = 1; i <= n; ++i){
	if(ancestor[i][k - 1] != -1){
	  sets[i][k] = merge(sets[i][k - 1], sets[ancestor[i][k - 1]][k - 1]);
	  ancestor[i][k] = ancestor[ancestor[i][k - 1]][k - 1];
	}
      }
    }
  }
  vector<int> pathUnion(int u, int v){
    if(level[u] > level[v])
      swap(u, v);
    vector<int> ans;
    for(int k = K - 1; k >= 0; --k){
      if(level[v] - (1 << k) >= level[u]){
	ans = merge(ans, sets[v][k]);
	v = ancestor[v][k];
      }
    }
    if(u == v){
      ans = merge(ans, sets[u][0]);
      return ans;
    }
    for(int k = K - 1; k >= 0; --k){
      if(ancestor[v][k] != ancestor[u][k]){
	ans = merge(ans, sets[u][k]);
	ans = merge(ans, sets[v][k]);
	u = ancestor[u][k];
	v = ancestor[v][k];
      }
    }
    ans = merge(ans, sets[u][0]);
    ans = merge(ans, sets[v][0]);
    ans = merge(ans, sets[ancestor[u][0]][0]);
    return ans;
  }
};

int main(){
  int n, m, q;
  cin >> n >> m >> q;
  auto g = new Graph(n);
  int u, v;
  for(int i = 1; i < n; ++i){
    cin >> u >> v;
    g -> addEdge(u, v);
  }
  int p;
  for(int i = 1; i <= m; ++i){
    cin >> p;
    g -> addPeople(i, p);
  }
  Tree* t = new Tree(g);
  for(int i = 0; i < q; ++i){
    cin >> u >> v >> p;
    auto ret = t -> pathUnion(u, v);
    cout << (p < ret.size() ? p : ret.size());
    int j = 0;
    for(auto it = ret.begin(); it != ret.end(); ++it){
      if(j == p){
	break;
      }
      cout << " " << *it;
      ++j;
    }
    cout << endl;
  }
  return 0;
}
