//
//  Crazy Search.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/10/25.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <hash_set>
using namespace std;
int cracySearch(string &text, int n) {
    hash_set<string> S;
	int length=text.length();
    for (int i=0; i<=length-n; i++) {
		string s=text.substr(i,n);
		S.insert(s);
    }
	return S.size();
}
int main(){
    ifstream inputdata("Crazy Search/inputdata.txt");
    ofstream outputdata("Crazy Search/outputdata.txt");
	int n, nc;
	inputdata>>n>>nc;
	while(n>0||nc>0){
		string text;
		inputdata>>text;
		int result=cracySearch(text,n);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>n>>nc;
	}
    inputdata.close();outputdata.close();
    return 0;
}