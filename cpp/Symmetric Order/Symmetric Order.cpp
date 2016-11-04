//
//  Symmetric Order.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 15/2/4.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <iterator>
using namespace std;
void symmetricOrder(list<string> &names){
	int n=names.size();
	int m=(n%2==1)?(n/2+1):n/2;
	int k=1;
	list<string>::iterator i=++(names.begin()), j=(names.end());
	while (k<m) {
		names.insert(j, *i);
		names.erase(i++);
		i++; j--;
		k++;
	}
}
int main(){
    ifstream inputdata("Symmetric Order/inputdata.txt");
    ofstream outputdata("Symmetric Order/outputdata.txt");
	int n, number=0;
	inputdata>>n;
	while (n>0) {
		list<string> names;
		for (int i=0; i<n; i++) {
			string name;
			inputdata>>name;
			names.push_back(name);
		}
		symmetricOrder(names);
		outputdata<<"SET "<<(++number)<<endl;
		copy(names.begin(), names.end(), ostream_iterator<string>(outputdata, "\n"));
		cout<<"SET "<<(number)<<endl;
		copy(names.begin(), names.end(), ostream_iterator<string>(cout, "\n"));
		inputdata>>n;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}