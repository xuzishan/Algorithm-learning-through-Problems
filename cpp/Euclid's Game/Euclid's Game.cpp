//
//  Euclid's Game.cpp
//  Algorithms
//
//  Created by 徐子珊 on 16-4-6.
//  Copyright (c) 2016年 徐子珊. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string euclidGame(int a, int b){
	bool who=false;
	while(b){
		who=(!who);
		int r=a%b;
		a=b;
		b=r;
	}
	if(who)
		return "Stan wins";
	return "Ollie wins";
}
int main(){
    ifstream inputdata("Euclid's Game/inputdata.txt");
    ofstream outputdata("Euclid's Game/outputdata.txt");
	int a, b;
	inputdata>>a>>b;
	while(a&&b){
		if (a<b)
			swap(a, b);
		string result=euclidGame(a, b);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>a>>b;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}