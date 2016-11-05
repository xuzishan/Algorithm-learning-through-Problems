//
//  RSA Factorization.cpp
//  Algorithms
//
//  Created by 徐子珊 on 16-4-21.
//  Copyright (c) 2016年 徐子珊. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../utility/integer.h"
#include "../utility/bigint.h"
#include <assert.h>
size_t toInteger(BigInt x){
	assert(x.size()<11);
	ostringstream os;
	os<<x;
	istringstream is(os.str());
	size_t a;
	is>>a;
	return a;
}
string RSAFactorization(string &n, int k){
	BigInt x(n), Zero(0);
	vector<size_t> primes=k>1?sift(100000/(k-1)):sift(100000);
	size_t m=primes.size();
	ostringstream s;
	for(size_t i=0; i<m; i++){
		BigInt q(primes[i]);
		pair<BigInt, BigInt> t=dive(x, q);
		if (t.second==Zero){
			BigInt p=t.first;
			s<<q<<" * "<<p;
			break;
		}
	}
	return s.str();
}
int main(){
    ifstream inputdata("RSA Factorization/inputdata.txt");
    ofstream outputdata("RSA Factorization/outputdata.txt");
	string n;
	int k;
	while(inputdata>>n>>k){
		string result=RSAFactorization(n, k);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}