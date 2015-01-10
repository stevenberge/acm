/*
题目3 : Suzhou Adventure
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Little Hi is taking an adventure in Suzhou now. There are N beautiful villages in Suzhou which are numbered from 1 to N. They connected by N-1 roads in such a way that there is excactly one way to travel from one village to another. Little Hi gives each village a score according to its attractiveness. He is visiting village 1 now and plans to visit excatly M villages (including village 1) and maxize the total score of visited villages. Further more, K villages are recommended by Little Ho. He does not want to miss these recommended villages no matter what their attractiveness scores are.

Note that Little Hi visits every village on his travel route. Passing a village without visiting it is not allowed. Please find the maximum total score Little Hi can get.

输入
The first line contains 3 integers N(1 <= N <= 100), K(1 <= K <= 5) and M(1 <= M <= N), representing the number of villages, the number of recommended villages and the number of villages Little Hi plans to visit.
The second line contains N integers, the attractiveness scores of villages. The scores are between 1 to 100.
The third line contains M integers, the list of recommended villages.
The following N-1 lines each contain two integers a and b, indicating that village a and village b are connected by a road.

输出
The maximum scores Little Hi can get. If there is no solution output -1.

样例输入
5 2 4
1 2 3 4 5
3 4
1 2
1 3
1 4
2 5
样例输出
 */ 


#include <iostream>
#include <vector>
using namespace std;
//#define pair<int, int> EDG;
void dfs(const vector<vector<int> > &graph, const vector<int> & weight, const int k, int p, int v, vector<vector<int> > &ds, vector<bool> &nd){
    ds[v] = vector<int>(k+1, 0);
    
    for(int t = 0; t<graph[v].size(); t++){
        int u = graph[v][t];
        if(u == p) continue;
        dfs(graph, weight, k, v, u, ds, nd);
        vector<int> tmp(k+1, -1);
        for(int j = k; j>=0; j--){
            for(int i = 0; i<=j; i++){
                if(ds[u][i]<0 || ds[v][j-i]<0) continue; // forbidden
                tmp[j] = max(tmp[j], ds[v][j-i]+ds[u][i]);
            }
        }
        ds[v] = tmp;
    }

    for(int i = k-1; i>=0; i--){
        if(ds[v][i]<0) ds[v][i+1] = -1;
        else ds[v][i+1] = ds[v][i] + weight[v];
    }
    if(nd[v])  ds[v][0] = -1;
  
}

int main(){
    int n, m, k; cin>>n>>m>>k;
    vector<int> weight(n);
    for(int i = 0; i<n; i++) cin>>weight[i];
    vector<vector<int> > graph(n);
    vector<bool> nd(n, false);
    for(int i = 0; i<m; i++){
        int a; cin>>a; a--;
        nd[a] = true;
    }
    for(int i = 0; i<n-1; i++) {
        int a, b; cin>>a>>b; a--, b--;
        graph[a].push_back(b), graph[b].push_back(a);
    }
    vector<vector<int> > ds(n);
    dfs(graph, weight,k,-1,0,ds,nd);
    cout<<ds[0][k]<<endl;
    return 0;
}
