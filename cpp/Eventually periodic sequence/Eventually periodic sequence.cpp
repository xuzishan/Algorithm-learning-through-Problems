//
//  Eventually periodic sequence.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/4.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <hash_map>
#include <stack>
#include <string>
using namespace std;
int calculate(int N, int x, vector<string> RPN) {
	stack<unsigned long long> S;
	int n=RPN.size();
	string operators="+*%";
	for (int i=0; i<n; i++) {
		size_t op=operators.find(RPN[i]);
		if (op<=2) {
			unsigned long long op2=S.top(); S.pop();
			unsigned long long op1=S.top(); S.pop();
			switch (op) {
				case 0://"+"
					S.push(op1+op2);
					break;
				case 1://"*"
					S.push(op1*op2);
					break;
				case 2://"%"
					S.push(op1%op2);
					break;
				default:
					break;
			}
		} else {
			if (RPN[i]=="x")
				S.push(x);
			else if	(RPN[i]=="N")
					S.push(N);
			else S.push(int(atoi(RPN[i].c_str())));
		}
	}
	return S.top();
}
int eventuallyPeriodicSequence(int N, int n, vector<string> &RPN) {
	int k=0, x=n;
	hash_map<int, int> A;
	int i=A[x];
	while (!i) {
		A[x]=++k;
		x=calculate(N, x, RPN);
		i=A[x];
	}
	return k-i+1;
}
int main(){
    ifstream inputdata("Eventually periodic sequence/inputdata.txt");
    ofstream outputdata("Eventually periodic sequence/outputdata.txt");
	int N, n;
	inputdata>>N>>n;
	while (N>0 || n>0) {
		string s, item;
		getline(inputdata, s);
		istringstream strstr(s);
		vector<string> RPN;
		while (strstr>>item)
			RPN.push_back(item);
		int result=eventuallyPeriodicSequence(N, n, RPN);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>N>>n;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}