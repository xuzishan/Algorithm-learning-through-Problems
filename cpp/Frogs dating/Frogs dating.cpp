//
//  Frogs dating.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/4/19.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
#include "../utility/integer.h"
string frogsDating(int x, int y, int m, int n, unsigned L){
	unsigned long long a=n>m?n-m:m-n;
	long long b=n>m?x-y:y-x;
	vector<unsigned long long> A=modularLinearEquationSolver(a, b, L);
	ostringstream s;
	if (A.empty())
		s<<"Impossible";
	else
		s<<*(min_element(A.begin(), A.end()));
	return s.str();
}
int main(){
    ifstream inputdata("Frogs dating/inputdata.txt");
    ofstream outputdata("Frogs dating/outputdata.txt");
	unsigned x, y, m, n, L;
	inputdata>>x>>y>>m>>n>>L;
	string result=frogsDating(x, y, m, n, L);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
