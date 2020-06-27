#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <algorithm>

using namespace std;

vector<int> RMQ(const vector<int>& arr, const int n, const int k){
    deque<int> max_vector;
    deque<int> min_vector;
    vector<int> ret(n, 0);
    //    int max_span;
    int prev = -1;
    for(int j = 0; j < n; ++j){
        while(!max_vector.empty() && arr[j] > arr[max_vector.back()]){
            max_vector.pop_back();
        }
        max_vector.push_back(j);
        while(!min_vector.empty() && arr[j] < arr[min_vector.back()]){
            min_vector.pop_back();
        }
        min_vector.push_back(j);
        while(arr[max_vector.front()] - arr[min_vector.front()] > k){
            if(max_vector.front() > min_vector.front()){
                prev = min_vector.front();
                min_vector.pop_front();
            }else{
                prev = max_vector.front();
                max_vector.pop_front();
            }
        }
        ret[j] = j - prev;
    }
    return ret;
}

int main(){
  int n, s, l;
  cin >> n >> s >> l;
  vector<int> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  auto dist = RMQ(arr, n, s);
  if(dist.back() < l){
    cout << -1 << endl;
    return 0;
  }
  vector<int> table(n + 1, numeric_limits<int>::max());
  table[0] = 0;
  for(int i = 1; i <= n; ++i){
    if(dist[i - 1] >= l){
      for(int j = min(dist[i - 1], i); j >= l; --j){
	if(table[i - j] < numeric_limits<int>::max()){
	  table[i] = 1 + table[i - j];
	  break;
	}
      }
    }
  }
  cout << (table.back() < numeric_limits<int>::max() ? table.back() : -1) << endl;
  return 0;
}
