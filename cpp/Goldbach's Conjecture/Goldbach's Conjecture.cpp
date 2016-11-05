//
//  Goldbach's Conjecture.cpp
//  Algorithms
//
//  Created by 徐子珊 on 16-4-8.
//  Copyright (c) 2016年 徐子珊. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include "../utility/integer.h"
using namespace std;
int goldbachConjecture(unsigned long n){
	int count=0;
	vector<size_t> p=sift(n);
	size_t i=0;
	while(i<p.size()&&p[i]<=n/2){
		size_t x=n-p[i];
		if (find(p.begin(), p.end(), x)!=p.end())
			count++;
		i++;
	}
	return count;
}
int main(){
    ifstream inputdata("Goldbach's Conjecture/inputdata.txt");
    ofstream outputdata("Goldbach's Conjecture/outputdata.txt");
	int n;
	inputdata>>n;
	while(n){
		int result=goldbachConjecture(n);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>n;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}