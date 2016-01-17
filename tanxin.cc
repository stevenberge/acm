/*
http://www.aiuxian.com/article/p-2442291.html
有一批文件需要分配到不同的机器上。每一个文件需要分配到三个不同的机器上，而每个机器有一个接受文件数量的上限。问，给出一个算法说明如何分配才能达到最优？
 */

#include <iostream>
#include <vector>
#include <queue>
#define MAXCOPIES 100
using namespace std;
struct ele{
	int machineId;
	int capacity;
        ele(){}
	ele(int a, int b){
		machineId = a, capacity = b;
	}
	bool operator < (const ele & a) const{ 
		return capacity < a.capacity;
	}
};

vector<vector<int> > distrib(vector<int> &machines, vector<int> &files){
	priority_queue<ele> q;
	vector<vector<int> > filePos(files.size());
	vector<vector<int> > err;
	for(int i = 0; i < machines.size(); i++){
		q.push(ele(i, machines[i]));
	}
	ele t[MAXCOPIES];
	for(int i = 0; i < files.size(); i++){
		for (int j = 0; j<files[i]; j++){
			if (q.empty()){
				return err; 
			}
			t[j] = q.top();
			filePos[i].push_back(t[j].machineId);
			t[j].capacity --;
			q.pop();
		}
		for (int j = 0; j<files[i]; j++){
			if (t[j].capacity == 0) break;
			q.push(t[j]);
		}
	}
	return filePos;
}
int main(){
        int a[3] = {1, 2, 3}, b[3] = {2, 2, 2};
	vector<int> machines(a, a+3) , files(b, b+3);
	vector<vector<int> > res  = distrib(machines, files);
	for(int i = 0 ; i< res.size(); i++){ 
		for(int j = 0; j<res[i].size(); j++)
			cout<<res[i][j]<<" "; 
		cout<<endl;
	}
	return 0;
}
