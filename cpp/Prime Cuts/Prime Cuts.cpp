//
//  Prime Cuts.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/4/7.
//  Copyright (c) 2016Äê xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "../utility/integer.h"
using namespace std;
vector<size_t> primeCuts(int N, int C){
	vector<size_t> a=sift(N);
	a.insert(a.begin(),1);
	int n=a.size();
	if (2*C<n)
		if(n%2){
			a.erase(a.begin(), a.begin()+(n-C)/2);
			a.erase(a.begin()+2*C-1, a.end());
		}else{
			a.erase(a.begin(), a.begin()+(n/2-C));
			a.erase(a.begin()+2*C, a.end());
		}
	return a;
}
int main(){
    ifstream inputdata("Prime Cuts/inputdata.txt");
    ofstream outputdata("Prime Cuts/outputdata.txt");
	int N, C;
	while(inputdata>>N>>C){
		vector<size_t> result=primeCuts(N, C);
		outputdata<<N<<" "<<C<<": ";
		copy(result.begin(), result.end(), ostream_iterator<int>(outputdata, " "));
		outputdata<<endl<<endl;
		cout<<N<<" "<<C<<": ";
		copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
		cout<<endl<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
