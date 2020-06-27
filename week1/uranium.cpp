#include <iostream>
#include <vector>
#include <algorithm>
     
using namespace std;

typedef long long ll;
     
ll cal(vector<ll>& dist, int i, int j){
  int m1 = (i + j) / 2;
  int m2 = (i + j + 1) / 2;
  return (dist[j + 1] - dist[m2]) - (dist[m1 + 1] - dist[i]);
}
     
int main(){
  int n, L;
  ll b;
  cin >> n >> L >> b;
  vector<ll> arr(n + 1);
  arr[0] = 0;
  for(int i = 1; i <= n; ++i){
    cin >> arr[i];
  }
  sort(arr.begin(), arr.end());
  for(int i = 1; i <= n; ++i){
    arr[i] += arr[i - 1];
  }
  int count = 0;
  int l = 0;
  int r = 0;
  while(r < n){
    while(l <= r && cal(arr, l, r) > b){
      ++l;
    }
    count = max(count, r - l + 1);
    ++r;
  }
  cout << count << endl;
  return 0;
}
