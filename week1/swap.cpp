#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main(){
  int n, q;
  cin >> n >> q;
  vector<vector<int>> square;
  vector<int> row(n + 1);
  vector<int> col(n + 1);
  for(int i = 0; i <= n; ++i){
    vector<int> v(n + 1);
    if(i > 0){
      for(int j = 1; j <= n; ++j){
	cin >> v[j];
      }
    }
    square.push_back(v);
    row[i] = i;
    col[i] = i;
  }
  string s;
  int r, c;
  for(int i = 0; i < q; ++i){
    cin >> s >> r >> c;
    if(s == "A"){
      cout << square[row[r]][col[c]] << endl;
    }else if(s == "R"){
      swap(row[r], row[c]);
    }else{
      swap(col[r], col[c]);
    }
  }
  return 0;
}
