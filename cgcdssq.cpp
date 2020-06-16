#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

int gcd(int a, int b){
  while(a != 0 && b != 0){
    if(a >= b){
      a %= b;
    }else{
      b %= a;
    }
  }
  return a + b;
}

void preprocess(unordered_map<int, ll>& Counter, const vector<int>& A, const int N){
  unordered_set<int> seen;
  unordered_map<int, ll> prev;
  for(int i = 0; i < N; ++i){
    unordered_map<int, ll> curr;
    unordered_set<int> new_set;
    for(int x : seen){
      int g = gcd(x, A[i]);
      if(curr.find(g) == curr.end()){
	curr[g] = prev[x];
      }else{
	curr[g] += prev[x];
      }
      new_set.insert(g);
    }
    new_set.insert(A[i]);
    if(curr.find(A[i]) == curr.end()){
      curr[A[i]] = 1;
    }else{
      ++curr[A[i]];
    }
    for(int x : new_set){
      if(Counter.find(x) == Counter.end()){
	Counter[x] = curr[x];
      }else{
	Counter[x] += curr[x];
      }
    }
    seen = new_set;
    prev = curr;
  }
}

int main(){
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  unordered_map<int, ll> Counter;
  preprocess(Counter, arr, n);
  int q, k;
  cin >> q;
  for(int i = 0; i < q; ++i){
    cin >> k;
    if(Counter.find(k) == Counter.end()){
      cout << 0 << endl;
    }else{
      cout << Counter[k] << endl;
    }
  }
  return 0;
}
