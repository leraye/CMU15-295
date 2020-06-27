#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> arr(n + 1, 0);
  for(int i = 1; i <= n; ++i){
    cin >> arr[i];
  }
  char c = 'a';
  string s;
  s.resize(n + 1, '*');
  int nxt;
  for(int i = 1; i <= n; ++i){
    if(s[i] == '*'){
      if(c - 'a' >= 26){
	cout << -1 << endl;
	return 0;
      }
      s[i] = c;
      nxt = arr[i];
      while(nxt != n + 1){
	if(s[nxt] != '*'){
	  cout << -1 << endl;
	  return 0;
	}
	s[nxt] = c;
	nxt = arr[nxt];
      }
      ++c;
    }
  }
  cout << s.substr(1, n) << endl;
  return 0;
}
