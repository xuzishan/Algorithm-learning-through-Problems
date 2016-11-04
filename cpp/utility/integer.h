//
//  integer.h
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/4/12.
//  Copyright (c) 2016Äê xu_zishan. All rights reserved.
//
#ifndef _INTEGER_H
#define _INTEGER_H
	#include <vector>
	using namespace std;
	void euclid(unsigned long long  a,
				unsigned long long b,
				unsigned long long &d,
				long long &x,
				long long &y);
	vector<unsigned long long> modularLinearEquationSolver(unsigned long long,
														   long long,
														   unsigned long long);
	vector<size_t> sift(size_t n); 

#endif /*_INTEGER_H*/