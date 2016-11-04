//
//  TheRobbery.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/29.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class Bank{
private:
    vector<int> weight;
    vector<int> cost;
    vector<int> x;
    int value;
    int w;
    int m;
    int n;
    int maxValue;
    void knapsack(int k);
public:
    Bank(vector<int> &W, vector<int> &C, int M);
	friend int theRoberry(vector<int> &W, vector<int> &C, int m);
};
Bank::Bank(vector<int> &W, vector<int> &C, int M){
	int N=W.size();
    n=N*(N+1)/2;
    weight=vector<int>();
    cost=vector<int>();
    x=vector<int>(n);
    m=M;
    value=0;
	w=0;
	maxValue=INT_MIN;
    for (int i=0; i<N; i++)
        for (int j=0; j<=i; j++) {
            weight.push_back(W[i]);
            cost.push_back(C[i]);
        }
}
void Bank::knapsack(int k){
    if (k>=n) {
        if (maxValue<value)
            maxValue=value;
        return;
    }
    for (int i=0; i<2; i++) {
        x[k]=i;
        if ((w+x[k]*weight[k])<=m) {
            w+=x[k]*weight[k];
            value+=x[k]*cost[k];
            knapsack(k+1);
            w-=x[k]*weight[k];
            value-=x[k]*cost[k];
        }
    }
}
int theRoberry(vector<int> &W, vector<int> &C, int m){
	Bank bank(W, C, m);
	bank.knapsack(0);
	return bank.maxValue;
}
int main(){
	ifstream inputdata("The Robbery/inputdata.txt");
	ofstream outputdata("The Robbery/outputdata.txt");
	int T;
	inputdata>>T;//读取案例数
	for(int t=0; t<T; t++){//处理每个案例
		int N, M;
		inputdata>>N>>M;//读取柜子数和最多能带走的重量
		vector<int> W(N),C(N);
		for(int i=0; i<N; i++)//填充重量数组
			inputdata>>W[i];
		for(int i=0; i<N; i++)//填充价值数组
			inputdata>>C[i];
		int m=theRoberry(W, C, M);//解决背包问题
		outputdata<<m<<endl;//输出计算结果
		cout<<m<<endl;
	}
	inputdata.close();
	outputdata.close();
	return 0;
}