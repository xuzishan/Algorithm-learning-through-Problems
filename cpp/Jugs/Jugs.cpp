//
//  Jugs.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/4/15.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "../utility/integer.h"
string jugs(int a, int b, int N){
	ostringstream s;
	long long x, y;
	unsigned long long d;
	euclid(a, b, d, x, y);
	int x0=N*x, y0=N*y;//丢番图方程的解
	int a1=0, b1=0,//当前出水桶，进水桶水量
		x1=-x0, y1=y0,//当前出水桶，进水桶尚余可操作桶数
		a2=a, b2=b,//出水桶，进水桶的容量
		*bb=&b1;//指向B桶
	char X='A', Y='B';//出水桶，进水桶
	if(x0>0){//进水桶为A
		swap(a2, b2);
		swap(X, Y);
		bb=&a1;
		x1=-y0;
		y1=x0;
	}
	while(*bb!=N){//B桶中水量未达标
		if(y1 && b1==0){//进水桶为空且可灌水，灌满
			b1=b2;
			y1--;
			s<<"fill "<<Y<<endl;
			continue;
		}
		if(x1 && a1==a2){//出水桶已满且可倾倒，倾倒
			a1=0;
			x1--;
			s<<"empty "<<X<<endl;
			continue;
		}
		if(b1<=a2-a1){//出水桶未满，用进水桶中所有水灌注
			a1=a1+b1;
			b1=0;
		}else{//用进水桶中水将出水桶灌满
			b1=b1-(a2-a1);
			a1=a2;
		}
		s<<"puor "<<Y<<" "<<X<<endl;
	}
	return s.str();
}
int main(){
    ifstream inputdata("Jugs/inputdata.txt");
    ofstream outputdata("Jugs/outputdata.txt");
	int a, b, N;
	while(inputdata>>a>>b>>N){
		string result=jugs(a, b, N);
		outputdata<<result<<"success"<<endl;
		cout<<result<<"success"<<endl;
	}
    inputdata.close();
	outputdata.close();
	return 0;
}