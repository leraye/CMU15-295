#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef long long ll;

int main(){
  int n;
  ll k;
  cin >> n;
  string sym, num, ky;
  unordered_map<ll, ll> counter;
  for(int i = 0; i < n; ++i){
    cin >> sym >> num;
    if(sym == "?"){
      k = stoll(num);
      if(counter.find(k) == counter.end()){
	cout << 0 << "\n";
      }else{
	cout << counter[k] << "\n";
      }
    }else{
      ky = "";
      for(char c : num){
	int x = c - '0';
	if(x & 1){
	  ky += "1";
	}else{
	  ky += "0";
	}
      }
      k = stoll(ky);
      if(sym == "+"){
	if(counter.find(k) == counter.end()){
	  counter[k] = 1;
	}else{
	  ++counter[k];
	}
      }else{
	--counter[k];
      }
    }
  }
  return 0;
}
