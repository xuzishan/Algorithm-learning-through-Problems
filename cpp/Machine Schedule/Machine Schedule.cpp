//
//  Machine Schedule.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/9/5.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
bool operator<(const set<int> &a, const set<int> &b){
	return a.size()<b.size();
}
class Comp{
public:
	bool operator()(set<int> &a, set<int> &b){
		return a<b;
	}
};
int machineSchedule(int n, int m, vector<int> &i, vector<int> &x, vector<int> &y) {
    vector<set<int>> mode(n+m, set<int>());
    set<int> jobs;//未处理任务集合
	int k=x.size();
    for (int j=0; j<k; j++) {
        mode[x[j]].insert(i[j]);//记录任务i的A机工作模式
        mode[n+y[j]].insert(i[j]);//记录任务i的B机工作模式
        jobs.insert(j);
    }
	set<int> r=mode[0].size()>mode[n+m-1].size()? mode[0]:mode[n+m-1];//首次开机要处理的任务
    int num=0;//机器重启次数
    while (!jobs.empty()) {//还有未处理任务
        num++;
		int* temp=new int[jobs.size()];
		int* p=set_difference(jobs.begin(), jobs.end(), r.begin(), r.end(), temp);//处理本次任务
		jobs=set<int>(temp, p);
		delete []temp;
        for (int j=0; j<n+m; j++) {//调整各模式可接受的任务
			temp=new int[mode[j].size()];
			p=set_difference(mode[j].begin(), mode[j].end(),r.begin(), r.end(), temp);
			mode[j]=set<int>(temp, p);
			delete []temp;
        }
		int j=distance(mode.begin(), max_element(mode.begin(), mode.end(),Comp()));//可处理最多任务的模式
        r=mode[j];//下次处理的任务
    }
    return num;
}
int main(){
    ifstream inputdata("Machine Schedule/inputdata.txt");
    ofstream outputdata("Machine Schedule/outputdata.txt");
	int n;
	inputdata>>n;
	while(n>0){
		int m, k;
		inputdata>>m>>k;
		vector<int> i(k), x(k), y(k);
		for(int j=0; j<k; j++)
			inputdata>>i[j]>>x[j]>>y[j];
		int result=machineSchedule(n,m,i,x,y);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>n;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}