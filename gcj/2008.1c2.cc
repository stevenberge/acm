#include <cmath>
#include <string.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

typedef long long int ll;

// 大整数取余数
// @param: ys 缓存 [l, r] 对3 7的余数
// @param: m =2, 3, 5, 7
int div(vector<vector<vector<int> > > &ys, int a[], int l, int r, int m){
  assert(l<=r);
  if(m == 2) return  a[r]%2;
  if(m == 5) return  a[r]%5;
  if(ys[l][r][m==3] >=0 ) return ys[l][r][m==3];
  if(l==r) return ys[l][r][m==3] = a[l]%m;
  if(m == 3)  return ys[l][r][m==3] = (div(ys, a, l, r-1, m) + a[r] )%m; 
  if(m == 7) return ys[l][r][m==3] = (div(ys, a, l, r-1, m)*10 + a[r] )%m;
}

// 状态压缩dp, k压缩了区间[l, r]对2,3,5,7的余数
// cnt[0, i][k] = E{ f([0, j-1][k1], [j, i][k2]), j=0~i, 
//        k1+k2=>k or k1-k2=>k or j=0 && k2=k}
ll dp(int a[], int n){
  // 状态压缩方法: 2,3,5,7 => 210
  vector<vector<ll> > cnt(n, vector<ll>(210, 0));
  vector<vector<vector<int> > > ys(n, vector<vector<int> >(n, vector<int>(2, -1)));
  for(int i=0; i<n; i++){
    // [0, i] => [0,j-1], [j, i]
    for(int j = i; j>=0; j--){
      // 取余数
      int d2 = div(ys, a, j, i, 2), d3 = div(ys, a, j, i, 3), d5 = div(ys, a, j, i, 5), d7 = div(ys, a, j, i, 7);
      //cout<<j<<"->"<<i<<":"<<d2<<","<<d3<<","<<d5<<","<<d7<<endl;
      if(j==0){
        // 压缩d2~d7 到 d
        int d = 105*d2+35*d3+7*d5+d7;
        cnt[i][d] += 1;
      }
      else
      for(int k = 0; k<210; k++){
        int t2 = k/105%2, t3 = k/35%3, t5 = k/7%5, t7=k%7;
        int t = 105*((t2+2-d2)%2) +35*((t3+3-d3)%3) +7*((t5+5-d5)%5) +((t7+7-d7)%7);
        cnt[i][k] += cnt[j-1][t];
        t = 105*((t2+d2)%2) +35*((t3+d3)%3) +7*((t5+d5)%5) +((t7+d7)%7);
        cnt[i][k] += cnt[j-1][t];
      }
    }
  }
  ll res = 0;
  for(int k = 0; k<210; k++){
    int t2 = k/105%2, t3 = k/35%3, t5 = k/7%5, t7=k%7;
    if(!(t2&&t3&&t5&&t7)) res+= cnt[n-1][k];
  }
  return res;
}

int main(){
  int N; cin>>N;
  for(int ii = 0; ii< N; ii++){
  char buf[100];
  cin>>buf;
  int a[100];
  int n = strlen(buf);
  for(int i = 0; i<n; i++) a[i] = buf[i]-'0';
  cout<<"Case #"<<ii+1<<": "<<dp(a, n)<<endl;
  }
  return 0;
}
