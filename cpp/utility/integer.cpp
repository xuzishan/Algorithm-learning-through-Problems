//
//  integer.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/4/19.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <bitset>
#include "bigint.h"
	#include <vector>
	#include <bitset>
unsigned long long mod(long long a, unsigned long long m){
	long long x=a%(long long)m;
	if(x<0)
		x+=m;
	return (unsigned long long)x;
}
void euclid(unsigned long long a,
			unsigned long long b,
			unsigned long long &d,
			long long &x,
			long long &y){
	if(b==0){
		d=a;
		x=1;
		y=0;
		return;
	}
	euclid(b, a%b, d, x, y);
	long long x1=y;
	y=x-(a/b)*y;
	x=x1;
}
vector<unsigned long long> modularLinearEquationSolver(unsigned long long a,
													   long long b,
													   unsigned long long n){
	unsigned long long d;
	long long x, y;
	vector<unsigned long long> S;
	euclid(a, n, d, x, y);
	if (!(b%d)){
		unsigned long long x0=mod(x*(b/d),n);
		for(size_t i=0; i<d; i++)
			S.push_back((x0+i*(n/d))%n);
	}
	return S;
}
vector<size_t> sift(size_t n){
	bitset<100001> b;
	b.set();
	b[0]=0, b[1]=0;
	int i=2;
	if(n%2)n++;
	while(i<=n/2){
		int j;
		for(j=2; j*i<n; j++){
			b[j*i]=0;
		}
		i++;
		while(i<=n/2&&b[i]==0)i++;
	}
	vector<size_t> a;
	for(i=1; i<=n; i++)
		if(b[i])
			a.push_back(i);
	return a;
}