//
//  Cow Counting.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/3/19.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
string cowCounting(int N, int L){
	int x=0;
	vector<int> a;
	do{
		int r=N%9;
		a.push_back(r);
		N/=10;
	}while(N);
	int i=0, j;
	while(a[i]==0)i++;
	j=i;
	string s;
	if (L<9)
		while(i<a.size()){
			if (a[i]==L)
				a[i]++;
			i++;
		}
	while(j<a.size())
		s+='0'+a[j++];
	return s;
}
int main(){
    ifstream inputdata("Cow Counting/inputdata.txt");
    ofstream outputdata("Cow Counting/outputdata.txt");
	int N, L;
	inputdata>>N>>L;
	string result=cowCounting(N, L);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
