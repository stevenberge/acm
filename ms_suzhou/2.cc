/*
 * 题目2 : Colorful Lecture Note
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Little Hi is writing an algorithm lecture note for Little Ho. To make the note more comprehensible, Little Hi tries to color some of the text. Unfortunately Little Hi is using a plain(black and white) text editor. So he decides to tag the text which should be colored for now and color them later when he has a more powerful software such as Microsoft Word.

There are only lowercase letters and spaces in the lecture text. To mark the color of a piece of text, Little Hi add a pair of tags surrounding the text, <COLOR> at the beginning and </COLOR> at the end where COLOR is one of "red", "yellow" or "blue".

Two tag pairs may be overlapped only if one pair is completely inside the other pair. Text is colored by the nearest surrounding tag. For example, Little Hi would not write something like "<blue>aaa<yellow>bbb</blue>ccc</yellow>". However "<yellow>aaa<blue>bbb</blue>ccc</yellow>" is possible and "bbb" is colored blue.

Given such a text, you need to calculate how many letters(spaces are not counted) are colored red, yellow and blue.

输入
Input contains one line: the text with color tags. The length is no more than 1000 characters.

输出
Output three numbers count_red, count_yellow, count_blue, indicating the numbers of characters colored by red, yellow and blue.

样例输入
<yellow>aaa<blue>bbb</blue>ccc</yellow>dddd<red>abc</red>
样例输出
3 6 3
*/

#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

int main(){
    stack<int> colors;
    string s0, s;//="<yellow>aaa<blue>bbb</blue>ccc</yellow>dddd<red>abc</red>";
    char buf[10000];
    cin.getline(buf, 10000);
    for(int i = 0; buf[i]; i++){
      if(buf[i] == ' ') continue;
      s.push_back(buf[i]);
    }
    cout<<s<<endl;
    
    int cnt[4];
    memset(cnt, 0, sizeof(cnt));
    
    int i = 0;
    while(i< s.length()){
        int j = i;
        while(j< s.length() && s[j] == ' ') j++;
        if(j< s.length() && s[j] == '<'){
            j++;
            while(s[j]==' ') j++;
            if(s[j]=='/'){
                colors.pop();
            }
            else{
                if(s[j] == 'r') colors.push(1);
                else if(s[j]=='y') colors.push(2);
                else colors.push(3);
            }
            while(s[j]!='>') j++;
            j++;
            i = j;
        }
        else{
            while(j< s.length() && s[j] != '<' ){
                //cout<<colors.top()<<endl;
                //cout<<s[j];
                if(s[j] != ' ' && colors.size()) cnt[colors.top()] ++;
                j++;
            }
            //cout<<endl;
            i = j;
        }
    }
    cout<<cnt[1]<<" "<<cnt[2]<<" "<<cnt[3]<<endl;
    return 0;
}

