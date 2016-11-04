//
//  Number Base Conversion.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/4/12.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <hash_map>
#include "../utility/bigint.h"
char d[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

BigInt bToTen(int B, string &a){
	hash_map<char, int> digit;
	for(int i=0; i<62; i++)
		digit.insert(make_pair(d[i], i));
	BigInt Bk(1), Base(B), v(digit[a[a.length()-1]]);
	for(string::reverse_iterator i=a.rbegin()+1; i!=a.rend(); i++){
		Bk=Bk*Base;
		v=v+BigInt(digit[*i])*Bk;
	}
	return v;
}
int digitValue(BigInt &digit){
	int n=digit.size();
	string v=digit.getValue();
	int s=0;
	for(int i=0; i<n; i++)
		s=10*s+v[i]-'0';
	return s;
}
string tenToB(int B, BigInt x){
	hash_map<int, char> digit;
	for(int i=0; i<62; i++)
		digit.insert(make_pair(i, d[i]));
	BigInt zero(0);
	string s;
	do{
		pair<BigInt, BigInt> p=dive(x, BigInt(B));
		s+=digit[digitValue(p.second)];//.getValue();
		x=p.first;
	}while(x!=zero);
	return string(s.rbegin(), s.rend());
}
string numberBaseConversion(int B1, int B2, string a){
	BigInt x=bToTen(B1, a);
	return tenToB(B2, x);
}
int main(){
    ifstream inputdata("Number Base Conversion/inputdata.txt");
    ofstream outputdata("Number Base Conversion/outputdata.txt");
	int T;
	inputdata>>T;
	for(int i=0; i<T; i++){
		int B1, B2;
		string a;
		inputdata>>B1>>B2>>a;
		string result=numberBaseConversion(B1, B2, a);
		outputdata<<B1<<" "<<a<<endl;
		outputdata<<B2<<" "<<result<<endl;
		outputdata<<endl;
		cout<<B1<<" "<<a<<endl;
		cout<<B2<<" "<<result<<endl;
		cout<<endl;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}