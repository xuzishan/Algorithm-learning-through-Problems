//
//  bigint.h
//  laboratory
//
//  Created by 徐子珊 on 16/4/12.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include "bigint.h"
using namespace std;
#include <assert.h>
vector<char> toVector(BigInt &a){
	size_t n=a.size();
	vector<char> a1;
	for(size_t i=0; i<n; i++)
		a1.push_back(a[i]);
	return a1;
}
BigInt::BigInt(string &x):value(x){}
BigInt::BigInt(int x){
	string s;
	do{
		s+=('0'+x%10);
		x/=10;
	}while(x);
	value=string(s.rbegin(), s.rend());
}
BigInt::BigInt(BigInt &x):value(x.value){}
BigInt::BigInt(vector<char> &x){
	for(int i=0; i<x.size(); i++)
		value.push_back('0'+x[i]);
}
size_t BigInt::size(){
	return value.size();
}
string BigInt::getValue(){
	return value;
}
char BigInt::operator[](size_t i){
	return value[i]-'0';
}
bool operator==(BigInt &a, BigInt &b){
	if (a.size()!=b.size())
		return false;
	return a.value==b.value;
}
bool operator<(BigInt &a, BigInt &b){
	if(a.size()!=b.size())
		return a.size()<b.size();
	return a.value<b.value;
}
bool operator<=(BigInt &a, BigInt &b){
	return a<b||a==b;
}
bool operator>(BigInt &a, BigInt &b){
	if(a.size()!=b.size())
		return a.size()>b.size();
	return a.value>b.value;
}
bool operator>=(BigInt &a, BigInt &b){
	return a>b||a==b;
}
ostream& operator<<(ostream &out, const BigInt &a){
	out<<a.value;
	return out;
}
pair<BigInt, BigInt> dive(BigInt &a, BigInt &b){
	if (a<b)
		return make_pair(BigInt(0), BigInt(a));
	if(a==b)
		return make_pair(BigInt(1), BigInt(0));
	size_t n=a.size(), m=b.size();
	string q;
	BigInt ten(10), r(a.getValue().substr(0,m));
	for(size_t i=0; i<=n-m; i++){
		int qi=9;
		while(qi>=0){
			if (BigInt(qi)*b<=r)
				break;
			qi--;
		}
		q+=('0'+qi);
		if(i<n-m)
			r=(r-BigInt(qi)*b)*ten+BigInt(a.getValue().substr(m+i,1));
		else
			r=r-BigInt(qi)*b;
	}
	while(q.length()>1&&q[0]=='0')
		q.erase(q.begin());
	return make_pair(BigInt(q), r);
}
BigInt operator+(BigInt &a, BigInt &b){
	int i=a.size()-1, j=b.size()-1;
	int carry=0;
	string s;
	while(i>=0&&j>=0){
		int ai=a[i--], bj=b[j--];
		int ck=ai+bj+carry;
		if(ck>=10){
			carry=1;
			ck%=10;
		}else
			carry=0;
		s+=('0'+ck);
	}
	while(i>=0){
		int ai=a[i--];
		int ck=ai+carry;
		if(ck>=10){
			carry=1;
			ck%=10;
		}else
			carry=0;
		s+=('0'+ck);
	}
	while(j>=0){
		int bj=b[j--];
		int ck=bj+carry;
		if(ck>=10){
			carry=1;
			ck%=10;
		}else
			carry=0;
		s+=('0'+ck);
	}
	if(carry)
		s+='1';
	string x(s.rbegin(), s.rend());
	return BigInt(x);
}
BigInt operator-(BigInt &a, BigInt &b){
	assert(a>=b);
	vector<char> a1=toVector(a);
	size_t n=a.size(), m=b.size();
	int i=n-1, j=m-1;
	string s;
	while(j>=0){
		char ck=a1[i]-b[j];
		if(ck<0){
			ck+=10;
			a1[i-1]--;
		}
		s+=ck+'0';
		i--; j--;
	}
	while(i>=0){
		char ck=a1[i];
		if(ck<0){
			ck+=10;
			a1[i-1]--;
		}
		s+=ck+'0';
		i--;
	}
	while(s.length()>1&&*(s.end()-1)=='0')
		s.erase(s.end()-1, s.end());
	string x(s.rbegin(), s.rend());
	return BigInt(x);
}
BigInt operator*(BigInt &a, BigInt &b){
	int n=a.size(), m=b.size();
	vector<char> c(n+m);
	for(int j=b.size()-1; j>=0; j--){
		int bj=b[j], carry=0, i;
		for(i=a.size()-1; i>=0; i--){
			int ai=a[i];
			c[i+j+1]=ai*bj+c[i+j+1]+carry;
			carry=c[i+j+1]/10;
			c[i+j+1]%=10;
		}
		if(carry)
			c[i+j+1]=carry;
	}
	while(c.size()>1&&c[0]==0)
		c.erase(c.begin());
	return BigInt(c);
}
BigInt Power(BigInt &t, int n){
	BigInt p(1);
	for(int i=0; i<n; i++)
		p=p*t;
	return p;
}
BigInt operator/(BigInt &a, BigInt &b){
	pair<BigInt, BigInt> result=dive(a, b);
	return result.first;
}
BigInt operator%(BigInt &a, BigInt &b){
	pair<BigInt, BigInt> result=dive(a, b);
	return result.second;
}
bool operator!=(BigInt &a, BigInt &b){
	return !(a==b);
}