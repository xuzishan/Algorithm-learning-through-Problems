//
//  The Embarrassed Cryptographer.cpp
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
using namespace std;
string theEmbarrassedCryptographer(int K, int L){
	vector<size_t> p=sift(L);
	size_t m=p.size();
	for(size_t i=0; i<m; i++){
		if(K%p[i]==0){
			ostringstream s;
			s<<"BAD "<<p[i];
			return s.str();
		}
	}
	return "GOOD";
}
int main(){
    ifstream inputdata("The Embarrassed Cryptographer/inputdata.txt");
    ofstream outputdata("The Embarrassed Cryptographer/outputdata.txt");
	int K, L;
	inputdata>>K>>L;
	while(K>0&&L>0){
		string result=theEmbarrassedCryptographer(K, L);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>K>>L;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}