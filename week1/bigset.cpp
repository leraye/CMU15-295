#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 50;
ll facts[maxn + 1][maxn + 1];
vector<int> counter(10, 0);

ll coef(int tot){
  int num = tot;
  ll ret = 1;
  for(int i = 0; i < 10; ++i){
    ret *= facts[num][counter[i]];
    num -= counter[i];
  }
  return ret;
}

ll sameLength(string s, int tot, bool head = true){
  int start = 0;
  if(head){
    start = 1;
  }
  ll ret = 0;
  for(int i = start; i < s[0] - '0'; ++i){
    if(counter[i] > 0){
      if(tot == 1){
	++ret;
      }else{
	--counter[i];
	ret += coef(tot - 1);
	++counter[i];
      }
    }
  }
  if(tot > 1){
    --counter[s[0] - '0'];
    ret += sameLength(s.substr(1), tot - 1, false);
  }
  return ret;
}

int main(){
  string s;
  cin >> s;
  int tot = s.size();
  facts[0][0] = 1;
  for(int i = 1; i <= maxn; ++i){
    facts[i][0] = facts[i][i] = 1;
    for(int j = 1; j < i; ++j){
      facts[i][j] = facts[i - 1][j - 1] + facts[i - 1][j];
    }
  }
  for(char c : s){
    ++counter[c - '0'];
  }
  if(counter[0] == 0){
    cout << sameLength(s, tot) << endl;
    return 0;
  }
  int num = tot - 1;
  ll ret = 1;
  --counter[0];
  for(int i = 0; i < 10; ++i){
    ret *= facts[num][counter[i]];
    num -= counter[i];
  }
  ++counter[0];
  ret += sameLength(s, tot);
  cout << ret << endl;
  return 0;
}
