//
//  Primes.cpp
//  Algorithms
//
//  Created by Ğì×ÓÉº on 16-4-21.
//  Copyright (c) 2016Äê Ğì×ÓÉº. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "../utility/integer.h"
int primes(int A, int B){
	vector<size_t> p=sift(B);
	int count=0;
	size_t n=p.size(), i=0;
	while(i<n&&p[i]<A)i++;
	while(i<n&&p[i]<=B){
		count++;
		i++;
	}
	return count;
}
int main(){
    ifstream inputdata("Primes/inputdata.txt");
    ofstream outputdata("Primes/outputdata.txt");
	int A, B;
	inputdata>>A>>B;
	while(A>=0&&B>0){
		int result=primes(A, B);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>A>>B;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}