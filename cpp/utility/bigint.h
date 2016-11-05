//
//  bigint.h
//  laboratory
//
//  Created by 徐子珊 on 16/4/12.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#ifndef _BIGINT_H
#define _BIGINT_H
	#include <string>
	#include <vector>
	using namespace std;
	class BigInt{
		string value;
	public:
		BigInt(int x);
		BigInt(string &x);
		BigInt(vector<char> &x);
		BigInt(BigInt &x);
		size_t size();
		char operator[](size_t i);
		string getValue();
		friend bool operator==(BigInt &a, BigInt &b);
		friend bool operator<(BigInt &a, BigInt &b);
		friend bool operator>(BigInt &a, BigInt &b);
		friend ostream& operator<<(ostream &out, const BigInt &a);
	};
	bool operator<=(BigInt &a, BigInt &b);
	bool operator>=(BigInt &a, BigInt &b);
	BigInt operator+(BigInt &a, BigInt &b);
	BigInt operator-(BigInt &a, BigInt &b);
	BigInt operator*(BigInt &a, BigInt &b);
	BigInt operator/(BigInt &a, BigInt &b);
	BigInt operator%(BigInt &a, BigInt &m);
	bool operator!=(BigInt &a, BigInt &b);
	pair<BigInt, BigInt> dive(BigInt &a, BigInt &b);
	BigInt Power(BigInt &t, int n);
#endif /*_BIGINT_H*/