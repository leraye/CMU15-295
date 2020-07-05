#include <iostream>
#include <string>
#include <functional>
#include <map>

using namespace std;

int table[10][10];

int main(){
  int n, m, k;
  cin >> n >> m >> k;
  string s;
  cin >> s;
  s = " " + s;
  map<int, char> S;
  S[0] = '#';
  for(int i = 1; i < n; ++i){
    if(s[i] != s[i + 1]){
      ++table[s[i] - 'a'][s[i + 1] - 'a'];
      S[i] = s[i];
    }
  }
  S[n] = s[n];
  int t, l, r;
  char c;
  string p;
  for(int i = 0; i < m; ++i){
    cin >> t;
    if(t == 1){
      cin >> l >> r >> c;
      auto pl = S.lower_bound(l);
      if(l > 1){
	auto lo = S.lower_bound(l - 1);
	char prev = lo -> second;
	char curr = pl -> second;
	if(prev != curr){
	  --table[prev - 'a'][curr - 'a'];
	  S.erase(l - 1);
	}
	if(prev != c){
	  ++table[prev - 'a'][c - 'a'];
	  S[l - 1] = prev;
	}
      }
      pl = S.lower_bound(l);
      auto pr = S.lower_bound(r);
      while(pl != pr){
	auto it = pl++;
	--table[it -> second - 'a'][pl -> second - 'a'];
	S.erase(it);
      }
      if(r < n){
	auto hi = S.lower_bound(r + 1);
	if(hi -> second != pr -> second){
	  --table[pr -> second - 'a'][hi -> second - 'a'];
	  S.erase(r);
	}
	if(hi -> second != c){
	  ++table[c - 'a'][hi -> second - 'a'];
	  S[r] = c;
	}
      }else{
	S[r] = c;
      }
      
    }else{
      cin >> p;
      int cnt = 0;
      for(int a = 0; a < k - 1; ++a){
	for(int b = a + 1; b < k; ++b){
	  cnt += table[p[a] - 'a'][p[b] - 'a'];
	}
      }
      cout << n - cnt << "\n";
    }
  }
  return 0;
}
