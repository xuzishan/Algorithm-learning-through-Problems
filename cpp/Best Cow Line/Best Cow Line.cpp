//
//  Best Cow Line.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/29.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string bestCowLine(string &line){
	int n=line.length();
    int i=0, i1=i+1, j=n-1, j1=j-1;
    string newLine;
    while (i<j) {
        while (i<j && line[i]==line[j] && line[i]==line[i1] && line[i1]==line[j1]) {
            newLine+=line[i++];
            i1++;
            newLine+=line[j--];
            j--;
        }
        if (i<j) {
            if (line[i]<line[j]) {
                newLine+=line[i++];
                i1++;
                continue;
            }
            if (line[i]>line[j]) {
                newLine+=line[j--];
                j1--;
                continue;
            }
            if (line[i1]>line[j1] || line[i]>line[j1]) {
                newLine+=line[j--];
                j1--;
                continue;
            }
            newLine+=line[i++];
            i1++;
        }
    }
    if (i==j)
        newLine+=line[i];
    return newLine;
}
int main(){
	ifstream inputdata("Best Cow Line/inputdata.txt");
	ofstream outputdata("Best Cow Line/outputdata.txt");
	int N;
	while(inputdata>>N){
		string line;
		char c;
		for(int i=0; i<N; i++){
			inputdata>>c;
			line+=c;
		}
		string newLine=bestCowLine(line);
		outputdata<<newLine<<endl;
		cout<<newLine<<endl;
	}
	inputdata.close();outputdata.close();
	return 0;
}
