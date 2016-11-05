//
//  Human Gene Functions.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/2.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
int A(char a, char b) {
    int score=0;
    if (a=='A') {
        switch (b) {
            case 'A': score = 5; break;
            case 'C': score = -1; break;
            case 'G': score = -2; break;
            case 'T': score = -1; break;
            default: score = -3;
        }
    }
    if (a=='C') {
        switch (b) {
            case 'A': score = -1; break;
            case 'C': score = 5; break;
            case 'G': score = -3; break;
            case 'T': score = -2; break;
            default: score = -4;
        }
    }
    if (a=='G') {
        switch (b) {
        case 'A': score = -2; break;
        case 'C': score = -3; break;
        case 'G': score = 5; break;
        case 'T': score = -2; break;
        default: score = -2;
        }
    }
    if (a=='T') {
        switch (b) {
        case 'A': score = -1; break;
        case 'C': score = -2; break;
        case 'G': score = -2; break;
        case 'T': score = 5; break;
        default: score = -1;
        }
    }
    if (a=='-') {
        switch (b) {
        case 'A': score = -3; break;
        case 'C': score = -4; break;
        case 'G': score = -2; break;
        default: score = -1; break;
        }
    }
    return score;
}
int humanGeneFunction(string &g1, string &g2){
	int m=g1.length(), n=g2.length();
    vector<vector<int>> s(m+1, vector<int>(n+1));
    for (int i=1; i<=m; i++)
        s[i][0]=s[i-1][0]+A(g1[i-1], '-');
    for (int j=1; j<=n; j++)
        s[0][j]=s[0][j-1]+A('-', g2[j-1]);
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++) {
            int a=s[i-1][j-1]+A(g1[i-1], g2[j-1]);
            int b=s[i-1][j]+A(g1[i-1],'-');
            int c=s[i][j-1]+A('-', g2[j-1]);
            s[i][j]=max(a, b);
			s[i][j]=max(s[i][j], c);
        }
    return s[m][n];
}
int main(){
    ifstream inputdata("Human Gene Functions/inputdata.txt");
    ofstream outputdata("Human Gene Functions/outputdata.txt");
	int T;
	inputdata>>T;
	for (int t=0; t<T; t++){
		string s1, s2;
		int x;
		inputdata>>x; inputdata>>s1;
		inputdata>>x; inputdata>>s2;
		int result=humanGeneFunction(s1, s2);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}