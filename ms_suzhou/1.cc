/*
 * 题目1 : Individual Income Tax
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
For incomes from wages and salaries, the progressive tax rate in excess of specific amount is applicable. The income amount taxable shall be the remainder after deducting 3500 yuan from the monthly income. The tax rate is below:

Grade Monthly Taxable Income
Tax Rate(%)
Income of 1,500 yuan or less
3%
That part of income in excess of 1,500 to 4,500 yuan
10%
That part of income in excess of 4,500 to 9,000 yuan
20%
That part of income in excess of 9,000 to 35,000 yuan
25%
That part of income in excess of 35,000 to 55,000 yuan
30%
That part of income in excess of 55,000 to 80,000 yuan
35%
That part of income in excess of 80,000 yuan
45%
Given the tax Little Hi paid, do you know his salary this month?

输入
Line 1: M, the tax Little Hi paid. (1 <= M <= 5,000,000)

输出
Line 1: Little Hi's salary. The number should be rounded dowm to the nearest integer.

提示
Little Hi's salary is 15692 yuan. The tax is calculated below:
The income amount taxable is 15692 - 3500 = 12192 yuan.
That part of income of 1500 or less: 1500 * 3% = 45 yuan.
That part of income in excess of 1,500 to 4,500 yuan: 3000 * 10% = 300 yuan.
That part of income in excess of 4,500 to 9,000 yuan: 4500 * 20% = 900 yuan.
That part of income in excess of 9,000 to 35,000 yuan: (12192 - 9000) * 25% = 798 yuan.
Total tax is 45 + 300 + 900 + 798 = 2043 yuan.

样例输入
2043
样例输出
15692*/

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
double t[6] = {1500, 4500, 9000, 35000, 55000, 80000},
       s[7] = {0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45};
double r[6] ;
int init(){
    for(int i = 0; i<6; i++){
        r[i] = (i>0?r[i-1] + s[i]*(t[i]-t[i-1]): 0 + s[i]*t[i]); 
        //cout<<t[i]<<":"<<r[i]<<":"<<s[i]<<endl;
    }
}
int main(){
    init();
    int n; double m; 
    cin>>n;
    
    double * p = lower_bound(r, r+6, n)-1;
    int i = p-r;
    
    if(p==r){
        m = n/s[0] + 3500;
    }
    else{
        m = (n-*p)/s[i+1] + t[i] + 3500;
    }
    
    int res = m;
    // double s1 = (res-3500-t[i])*s[i+1] + r[i], 
    //       s2 = (res+1-3500-t[i])*s[i+1] + r[i];
    // if(fabs(s1-n)>fabs(s2-n)) res ++;
    cout<< res<<endl;
    //cin>>res;
    return 0;
}
