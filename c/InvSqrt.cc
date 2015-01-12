#include <iostream>
//http://blogread.cn/it/article/3299?f=hot3
using namespace std;
float InvSqrt (float x) 
{
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i>>1);
	x = *(float*)&i;
	x = x*(1.5f - xhalf*x*x);
	return x;
}
int main(){
  cout<<InvSqrt(0.5)<<":"<<InvSqrt(976)<<endl;
  return 0;
}
