#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <string>

using namespace std;

int main(){
  int n;
  double R;
  cin >> n >> R;
  vector<double> arr(n);
  for(int i = 0; i < n; ++i){
    cin >> arr[i];
  }
  sort(arr.begin(), arr.end());
  vector<string> ret;
  for(auto it = arr.rbegin(); it != arr.rend(); ++it){
    if(*it <= R){
      int cnt = (int)floor(R / *it);
      while(cnt > 0){
	ret.push_back(to_string(1) + " " + to_string((int)*it));
	R -= (*it);
	cnt -= 1;
      }
    }
  }
  int c, i;
  double d;
  while(R > 0.01){
    d = numeric_limits<double>::max();
    for(int j = 0; j < n; ++j){
      int cnt = (int)ceil(arr[j] / R);
      if(R - arr[j] / cnt < d){
	d = R - arr[j] / cnt;
	i = j;
	c = cnt;
      }
    }
    R = d;
    string s = to_string(c);
    while(c > 0){
      s += " " + to_string((int)arr[i]);
      --c;
    }
    ret.push_back(s);
  }
  cout << ret.size() << endl;
  for(string s : ret){
    cout << s << endl;
  }
  return 0;
}
