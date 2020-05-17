/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 300
#define INF 0x3f3f3f3f
#define MAXF 400
#define P 19650827
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
typedef long long ll;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);
int n, m;
priority_queue<int, vector<int>, greater<int>> que;

int nq = 0;
int quee[MAX] = {0};//小根堆
void up(int p){//向上调整
    while(p>1){//p到达最顶端停止
        if(quee[p]<quee[p>>1]){//如果小于父节点
            swap(quee[p], quee[p >> 1]);//交换
            p >>= 1;//p向上一层
        }
        else{
            break;//如果不小于父节点就停下来
        }
    }
}

void down(int p){
    int s = p << 1;//s为左孩子
    while(s<=nq){//s到达堆大小为止
        if(s<nq&&quee[s]>quee[s+1])//如果左孩子大于右孩子s++
            s++;
        if(quee[p]>quee[s]){//如果父节点大于最小的节点
            swap(quee[p], quee[s]);//交换
            p = s;//向下移动一层
            s = p << 1;
        }
        else
            break;
    }
}

void push(int val){
    quee[++nq] = val;//插入一个数，插入到最后节点，
    up(nq);//向上调整最后节点
}

int top(){
    return quee[1];
}

void pop(){
    quee[1] = quee[nq--];//删除堆顶，将堆顶与最后一个交换，然后大小减一
    down(1);//向下调整堆顶
}

void remove(int k){
    quee[k] = quee[nq--];
    up(k);
    down(k);
}





int main()
{
    fcin >> n;
    int cz, cnu;
    while(n--){
        fcin >> cz;
        if(cz==1){
            fcin >> cnu;
            push(cnu);
        }
        else if(cz==2){
            int outc = top();
            fcout << outc << endl;
        }
        else{
            pop();
        }
    }

    fcin.close();
    fcout.close();

        return 0;
}