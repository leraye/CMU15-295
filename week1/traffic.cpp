#include <iostream>

using namespace std;

int main(){
  int n, d;
  cin >> n >> d;
  int p, t, g, r;
  bool pass = true;
  for(int i = 0; i < n; ++i){
    cin >> p >> t >> g >> r;
    if(t > p){
      pass = false;
      continue;
    }
    int diff = (p - t) % (g + r);
    if(diff > g){
      pass = false;
    }
  }
  if(pass){
      cout << "YES" << endl;
  }else{
      cout << "NO" << endl;
  }
  
  return 0;
}
