#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int main(){
  vector <int> a= { 4,5,2,3,1};
  sort(a.begin(), a.end(), less<int>());
  priority_queue<int, vector<int>, less<int> > que;
  que.push(3); que.push(2); que.push(9); que.push(5); que.push(0);
  for(int i = 0; i<a.size(); i++){
    cout<<a[i]<<" ";
  }cout<<endl;
  while(!que.empty()){
    int s = que.top(); que.pop();
    cout<<s<<" ";
  }cout<<endl;
  return 0;
}
