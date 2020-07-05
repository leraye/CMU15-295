#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

const string REMOVE = "removeMin";
const string GET = "getMin";
const string INSERT = "insert";

int main(){
  string s;
  int num, n;
  int cnt = 0;
  priority_queue<int, vector<int>, greater<int>> q;
  vector<string> instructions;
  vector<int> nums;
  cin >> n;
  for(int i = 0; i < n; ++i){
    cin >> s;
    if(s == INSERT){
      cin >> num;
      q.push(num);
      instructions.push_back(s);
      nums.push_back(num);
    }else if(s == GET){
      cin >> num;
      while(!q.empty() && q.top() < num){
	cnt += 1;
	instructions.push_back(REMOVE);
	q.pop();
      }
      if(q.empty() || q.top() > num){
	cnt += 1;
	q.push(num);
	instructions.push_back(INSERT);
	nums.push_back(num);
      }
      instructions.push_back(s);
      nums.push_back(num);
    }else{
      if(q.empty()){
	instructions.push_back(INSERT);
	nums.push_back(0);
	cnt += 1;
      }else{
	q.pop();
      }
      instructions.push_back(s);
    }
  }
  cout << cnt + n << "\n";
  int i = 0;
  for(auto x : instructions){
    cout << x;
    if(x != REMOVE){
      cout << " " << nums[i];
      ++i;
    }
    cout << "\n";
  }
  return 0;
}
