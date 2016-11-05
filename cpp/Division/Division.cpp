//
//  Division.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/4/5.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "../utility/bigint.h"
string division(int t, int a, int b){
	ostringstream s;
	s<<"("<<t<<"^"<<a<<"-1)/"<<"("<<t<<"^"<<b<<"-1) ";
	int dgtNumber=(a-b)*log10(double(t));
	if(a%b||dgtNumber>100)
		s<<"is not an integer with less than 100 digits.";
	else{
		BigInt x(t);
		int m=BigInt(b).size();
		BigInt sum(1),p(1);
		int i=1;
		x=Power(x, b);
		while(i*b<=a-b+1){
			p=p*x;
			sum=sum+p;
			i++;
		}
		s<<sum;
	}
	return s.str();
}
int main(){
    ifstream inputdata("Division/inputdata.txt");
    ofstream outputdata("Division/outputdata.txt");
	int t, a, b;
	while(inputdata>>t>>a>>b){
		string result=division(t, a, b);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}