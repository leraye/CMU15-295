#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> arr(n);
  vector<int> vec;
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
    vec.push_back(arr[i]);
  }
  bool all_zero = false;
  vector<int> v;
  
  while(!all_zero){
    vector<int> ones;
    int count_zero = 0;
    for(int i = 0; i < n; ++i){
      if(arr[i] & 1){
	ones.push_back(i);
      }
      arr[i] >>= 1;
      if(arr[i] == 0){
	++count_zero;
      }
    }
    if(count_zero == n){
      all_zero = true;
    }
    if(ones.size() > 1){
      v = ones;
    }
  }
  int ans = 0;
  for(int i = 0; i < v.size(); ++i){
    for(int j = i + 1; j < v.size(); ++j){
      ans = max(ans, (vec[v[i]] & vec[v[j]]));
    }
  }
  cout << ans << endl;
  return 0;
}
