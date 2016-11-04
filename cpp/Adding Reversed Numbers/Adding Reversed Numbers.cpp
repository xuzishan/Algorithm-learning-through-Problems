//
//  Adding Reversed Numbers.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/2/27.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int reverseNumber(int x){//整数反转
	int a=0;
	while(x!=0){
		a=10*a+(x%10);
		x/=10;
	}
	return a;
}
int addReverseNumber(int a, int b){
	int x=reverseNumber(a), y=reverseNumber(b);
	int z=x+y;
	return reverseNumber(z);
}
int main(){
    ifstream inputdata("Adding Reversed Numbers/inputdata.txt");
    ofstream outputdata("Adding Reversed Numbers/outputdata.txt");
	int N;
	inputdata>>N;
	for (int i=0; i<N; i++){
		int x, y;
		inputdata>>x>>y;
		int z=addReverseNumber(x, y);
		outputdata<<z<<endl;
		cout<<z<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
