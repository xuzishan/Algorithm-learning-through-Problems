//
//  Cow Solitaire.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/3/19.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int getNumber(char c){
    switch (c) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return c-'0';
    }
}
class Solitaire{
	vector<vector<int>> A;
	int n, i, j;
public:
	int  value, currentValue;
	Solitaire(vector<vector<int>> a): A(a), n(a.size()), value(INT_MIN), currentValue(a[n-1][0]), i(n-1), j(0){}
	void cowSolitaire(int k);
};
void Solitaire::cowSolitaire(int k){
    if (k>=2*n-1) {//走到右上角
        if (currentValue>value)
            value=currentValue;
        return;
    }
    if (i==0) {//顶层只能向右走
        j++;
        currentValue+=A[i][j];
        cowSolitaire(k+1);
        currentValue-=A[i][j];
        j--;
    }else if (j==n-1) {//右边缘只能向上走
        i--;
        currentValue+=A[i][j];
        cowSolitaire(k+1);
        currentValue-=A[i][j];
        i++;
    }else{
        j++; //向右走
        currentValue+=A[i][j];
        cowSolitaire(k+1);
        currentValue-=A[i][j];
        j--;
        i--; //向上走
        currentValue+=A[i][j];
        cowSolitaire(k+1);
        currentValue-=A[i][j];
        i++;
    }
}
int main(){
    ifstream inputdata("Cow Solitaire/inputdata.txt");
    ofstream outputdata("Cow Solitaire/outputdata.txt");
	int N;
	char *s=new char[3];
	inputdata>>N;
    vector<vector<int>> a(N, vector<int>(N));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
			inputdata>>s;
            a[i][j]=getNumber(s[0]);
        }
    }
	delete []s;
	Solitaire sol(a);
	sol.cowSolitaire(1);
	outputdata<<sol.value<<endl;
	cout<<sol.value<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
