//
//  Power of Cryptography.cpp
//  Algorithms
//
//  Created by Ðì×ÓÉº on 16-4-20.
//  Copyright (c) 2016Äê Ðì×ÓÉº. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../utility/integer.h"
#include "../utility/bigint.h"
using namespace std;
struct PrimeFactor{
	size_t p, e;
	PrimeFactor(size_t prime, size_t index):p(prime), e(index){}
};
vector<PrimeFactor> primeFactor(size_t n, BigInt &p){
	vector<PrimeFactor> factors;
	BigInt x(p), Zero(0);
	size_t m=x.size();
	n=(m+1)/n;
	size_t power=1;
	for(int i=0; i<n; i++)
		power*=10;
	vector<size_t> f=sift(power);
	for(int i=0; i<f.size(); i++){
		BigInt fi(f[i]);
		pair<BigInt, BigInt> t=dive(x, fi);
		if(t.second==Zero){
			int e=0;
			while(t.second==Zero){
				e++;
				x=t.first;
				t=dive(x, fi);
			}
			factors.push_back(PrimeFactor(f[i], e));
		}
	}
	return factors;
}
size_t powerOfCryptography(int n, BigInt &p){
	vector<PrimeFactor> factors=primeFactor(n, p);
	size_t k=1;
	size_t m=factors.size();
	for(size_t i=0; i<m; i++){
		size_t x=1, pi=factors[i].p, ni=factors[i].e/n;
		for (size_t j=0; j<ni; j++)
			x*=pi;
		k*=x;
	}
	return k;
}
int main(){
    ifstream inputdata("Power of Cryptography/inputdata.txt");
    ofstream outputdata("Power of Cryptography/outputdata.txt");
	int n;
	string p;
	while(inputdata>>n>>p){
		size_t result=powerOfCryptography(n, BigInt(p));
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}