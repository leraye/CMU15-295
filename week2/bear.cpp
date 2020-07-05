#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_set>

using namespace std;

typedef long long ll;

int main(){
  int n, k, q;
  cin >> n >> k >> q;
  vector<ll> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  int t, id;
  priority_queue<ll, vector<ll>, greater<ll>> minq;
  unordered_set<int> seen;
  ll mx = 0;
  for(int i = 0; i < q; ++i){
    cin >> t >> id;
    if(t == 1){
      seen.insert(id);
      mx = max(mx, arr[id - 1]);
      minq.push(arr[id - 1]);
      if(minq.size() > k){
	minq.pop();
      }
    }else{
      if(!minq.empty() && arr[id - 1] >= minq.top() && arr[id - 1] <= mx && seen.find(id) != seen.end()){
	cout << "YES" << "\n";
      }else{
	cout << "NO" << "\n";
      }
    }
  }
  return 0;
}
