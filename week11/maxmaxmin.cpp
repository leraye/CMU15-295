#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int main(){
  int n, k;
  cin >> n >> k;
  vector<int> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  if(k == 1){
    cout << *min_element(arr.begin(), arr.end()) << endl;
  }else if(k >= 3){
    cout << *max_element(arr.begin(), arr.end()) << endl;
  }else{
    cout << max(arr[0], arr.back()) << endl;
  }
  return 0;
}
