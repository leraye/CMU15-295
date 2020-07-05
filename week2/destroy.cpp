#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct subset{
  int parent;
  int rank;
  ll sum;
} node;

int find(vector<node*>& arr, int i){
  if(arr[i] -> parent != i){
    arr[i] -> parent = find(arr, arr[i] -> parent);
  }
  return arr[i] -> parent;
}

void Union(vector<node*>& arr, int i, int j){
  int irt = find(arr, i);
  int jrt = find(arr, j);
  if(arr[irt] -> rank < arr[jrt] -> rank){
    arr[irt] -> parent = jrt;
    arr[jrt] -> sum += arr[irt] -> sum;
  }else if(arr[irt] -> rank > arr[jrt] -> rank){
    arr[jrt] -> parent = irt;
    arr[irt] -> sum += arr[jrt] -> sum;
  }else{
    arr[jrt] -> parent = irt;
    ++arr[irt] -> rank;
    arr[irt] -> sum += arr[jrt] -> sum;
  }
}

int main(){
  int n;
  cin >> n;
  vector<ll> arr(n + 1);
  arr[0] = -1;
  for(int i = 1; i <= n; ++i){
    cin >> arr[i];
  }
  vector<int> v(n);
  vector<node*> sets(n + 1);
  for(int i = 0; i < n; ++i){
    cin >> v[i];
    sets[v[i]] = new node;
    sets[v[i]] -> parent = v[i];
    sets[v[i]] -> rank = 1;
    sets[v[i]] -> sum = arr[v[i]];
  }
  vector<ll> ans = {0};
  unordered_set<int> seen;
  ll mx = 0;
  for(auto pt = v.rbegin(); pt != v.rend(); ++pt){
    if(seen.find(*pt - 1) != seen.end()){
      Union(sets, *pt - 1, *pt);
    }
    if(seen.find(*pt + 1) != seen.end()){
      Union(sets, *pt + 1, *pt);
    }
    int rt = find(sets, *pt);
    mx = max(mx, sets[rt] -> sum);
    ans.push_back(mx);
    seen.insert(*pt);
  }
  for(auto pt = ans.rbegin() + 1; pt != ans.rend(); ++pt){
    cout << *pt << "\n";
  }
  return 0;
}
