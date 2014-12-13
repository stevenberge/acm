#include <cmath>
#include <map>
#include <string.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

typedef long long int ll;
#define MOD 1000000007

ll tree[2000000];
int get(int l, int r, int idx, int a, int b){
  assert(idx>=0 && idx<2000000);
  if(a<=l && b>=r) return tree[idx];
  int mid =(l+r)/2;
  ll x = 0;
  if(a<=mid)
  x += get(l, mid, idx*2+1, a, min(b, mid));
  if(b>mid)
  x += get(mid+1, r, idx*2+2, max(a, mid+1), b);
  return x%MOD;
}
int add(int l, int r, int idx, int a, int d){
  int i0 = idx;
  while(l!=r){
    int mid = (l+r)/2;
    if(a<=mid) r=mid, idx=idx*2+1;
    else l = mid+1, idx=idx*2+2;
  }
  tree[idx]+=d, tree[idx]%=MOD;
  while(idx!=i0){
    int p = (idx-1)/2, sib=4*p+3-idx;
    tree[p] += d;// tree[idx]+tree[sib];
    tree[p] %= MOD;
    idx = p;
  }
}
void init(int l, int r, int idx){
  assert(idx>=0 && idx<2000000);
  assert(l<=r);
  if(l==r) { tree[idx] = 0; return; }
  int mid =(l+r)/2;
  init(l, mid, idx*2+1);
  init(mid+1, r, idx*2+r);
  tree[idx] = 0;//tree[idx*2+1]+tree[idx*2+2]; tree[idx] %= MOD;
}

int d[500001], b[500001];
ll t[500001];
int main(){
  int N; cin>>N;
  for(int i = 0; i<N; i++){
    int n, m;
    ll x, y, z;
    cin>>n>>m>>x>>y>>z;
    for(int j = 0; j<m; j++){
      cin>>t[j];
    }
    for(int j =0; j<n; j++){
      int k = j%m;
      d[j] = t[k];
      t[k] = (x*t[k]%z + y*(j+1))%z;//@error: x*t[k] should % z
    }

    // li san hua
    memcpy(b, d, sizeof(d));
    sort(b, b+n);
    //for(int j = 0; j<n; j++) cout<<b[j]<<" ";cout<<endl;
    assert(b[0]<=b[n-1]);

    map<int, int> mp;
    int idx = 0;
    mp[b[0]] = idx++;
    for(int j = 1; j<n; j++){
      if(b[j] == b[j-1]) continue;
      mp[b[j]] = idx++;
    }

    init(0, idx-1, 0);

    for(int j = 0; j<n; j++){
      int num = mp[d[j]];
      assert(num<=idx-1 && num>=0);

      int cnt = 0;
      if(num>0) cnt = get(0, idx-1, 0, 0, num-1) ;
      add(0, idx-1, 0, num, cnt+1);
    }
    cout<<"Case #"<<i<<": "<<get(0, idx-1, 0, 0, idx-1)<<endl;
  }
  return 0;
}

