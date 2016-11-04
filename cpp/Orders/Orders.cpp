//
//  Orders.cpp
//  Algorithms
//
//  Created by Ğì×ÓÉº on 13-7-7.
//  Copyright (c) 2013Äê Ğì×ÓÉº. All rights reserved.
//
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    ifstream inputdata("Orders/inputdata.txt");
    ofstream outputdata("Orders/outputdata.txt");
	string s;
	inputdata>>s;
	sort(s.begin(), s.end());
	outputdata<<s<<endl;
	cout<<s<<endl;
	while(next_permutation(s.begin(), s.end())){
		outputdata<<s<<endl;
		cout<<s<<endl;
	}
    inputdata.close();
	outputdata.close();
	return 0;
}