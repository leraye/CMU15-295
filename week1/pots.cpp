#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  int d = 0;
  int prev;
  sort(arr.begin(), arr.end());
  for(int i = 0; i < n; ++i){
    if(arr[i] > 0){
      ++d;
      prev = arr[i];
      for(int j = i + 1; j < n; ++j){
	if(arr[j] > prev){
	  prev = arr[j];
	  arr[j] *= -1;
	}
      }
      arr[i] *= -1;
    }
  }
  cout << d << endl;
  return 0;
}
