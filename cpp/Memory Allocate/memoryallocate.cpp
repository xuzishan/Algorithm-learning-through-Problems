//
//  memoryallocate.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/1/11.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "../utility/PriorityQueue.h"
using namespace std;
struct Program{
    int t, m, p;
    Program(int T, int M, int P):t(T), m(M), p(P){}
};
struct AddressPice{
    int startAddr, endAddr;
    AddressPice(int s, int e):startAddr(s), endAddr(e){}
	const int length(){
		return endAddr-startAddr+1;
	}
};
bool operator==(const AddressPice &a, const AddressPice &b){
    return a.startAddr == b.startAddr;
}
bool operator<(const AddressPice &a, const AddressPice &b) {
    return a.startAddr<b.startAddr;
}
struct WaitProgress{
    int timeLength;
    int memLength;
    WaitProgress(int t, int m):timeLength(t), memLength(m){}
};
bool operator==(const WaitProgress &a, const WaitProgress &b) {
    return a.timeLength==b.timeLength && a.memLength==b.memLength;
}
bool operator<(const WaitProgress &a, const WaitProgress &b) {
    return a.timeLength<b.timeLength;
}
struct Progress {
	int finishTime;
	AddressPice mem;
	Progress(int ft, AddressPice m): finishTime(ft),mem(m){}
};
bool operator==(const Progress &a, const Progress &b) {
    return a.finishTime==b.finishTime;
}
bool operator>(const Progress &a, const Progress &b) {
    return a.finishTime>b.finishTime;
}
void freeAddress(set<AddressPice> &S, Progress a){
	set<AddressPice>::iterator addr; 
    for (addr=S.begin(); addr != S.end(); addr++) {//扫描内存片集合
        if (addr->endAddr+1==a.mem.startAddr){//a接在addr之后
            AddressPice x=*addr;
            S.erase(addr);
            x.endAddr=a.mem.endAddr;
            S.insert(x);
            return;
        }else if (addr->startAddr-1==a.mem.endAddr) {//addr接在a之后
            AddressPice x=*addr;
            S.erase(addr);
            x.startAddr=a.mem.startAddr;
            S.insert(x);
            return;
        }
    }
    S.insert(a.mem);
}
set<AddressPice>::iterator allocAddress(set<AddressPice> &S, int length) {
    set<AddressPice>::iterator addr;
    for (addr=S.begin(); addr != S.end(); addr++) {
		if (addr->endAddr-addr->startAddr+1 >= length){
            break;
        }
    }
    return addr;
}
pair<int, int> memoryAlloc(vector<Program>& a, int N){
    int time=1, count=0, current=1;
    queue<WaitProgress> Q;
    set<AddressPice> S;
    PriorityQueue<Progress, greater<Progress>> P;
    P.push(Progress(time+a[0].p, AddressPice(0, a[0].m-1)));
    S.insert(AddressPice(a[0].m, N-1));
    while (!P.empty()) {
        time++;
        while (!P.empty()){//运行完毕的进程释放内存片
			Progress p=P.top();
            if (p.finishTime==time) {//p运行完毕
                freeAddress(S, p);
                P.pop();
            }else{
                break;
            }
        }
        while (!Q.empty()) {//等待队列
            WaitProgress p=Q.front();
            set<AddressPice>::iterator addr=allocAddress(S, p.memLength);
			if (addr != S.end() ){//申请到首地址最小的足量地址片
                Q.pop();//p出队
				if ((addr->endAddr-addr->startAddr+1)>p.memLength) {//分配给p后还有余量
                    int start=addr->startAddr+p.memLength+1;//剩余的首地址
                    int end=addr->endAddr;//尾地址
                    S.insert(AddressPice(start, end));//剩余片插入S
                }
                int finishTime=time+p.timeLength;//运行完成时间
                AddressPice addressPice=AddressPice(addr->startAddr, addr->startAddr+p.memLength-1);//所占地址片
                P.push(Progress(finishTime, addressPice));//加入运行
                S.erase(addr);//取出该地址片
            }else{//内存不够
                break;
            }
        }
        if (current<a.size()) {
            if (a[current].t==time) {
				set<AddressPice>::iterator addr=allocAddress(S, a[current].m);
                if (addr != S.end()) {//申请到首地址最小的足量地址片
					if (addr->endAddr-addr->startAddr+1>a[current].m) {
                        int start=addr->startAddr+a[current].m;
                        int end=addr->endAddr;
                        S.insert(AddressPice(start, end));
                    }
                    int finishTime=time+a[current].p;
                    AddressPice addressPice=AddressPice(addr->startAddr, addr->startAddr+a[current].m-1);
                    P.push(Progress(finishTime, addressPice));
                    S.erase(addr);
                }else{
                    Q.push(WaitProgress(a[current].p, a[current].m));
                    count++;
                }
                current++;
            }
        }
    }
    return make_pair(time, count);
}
int main(){
    ifstream inputdata("Memory Allocate/inputdata.txt");
    ofstream outputdata("Memory Allocate/outputdata.txt");
    int N, T, M, P;
    inputdata>>N;
    inputdata>>T>>M>>P;
    vector<Program> a=vector<Program>();
    while(T||M||P){
        a.push_back(Program(T, M, P));
        inputdata>>T>>M>>P;
    }
	pair<int, int> result=memoryAlloc(a, N);
	cout<<result.first<<endl;
	cout<<result.second<<endl;
	outputdata<<result.first<<endl;
	outputdata<<result.second<<endl;
    inputdata.close();
    outputdata.close();
    return 0;
}
