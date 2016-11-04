//
//  Triangular N_Queens.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/4/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
class Chessboard{
    vector<int> x;
    int first_col;//第一排皇后末尾位置的列号
    int seconde_row;//第二排皇后首个位置行号
    int seconde_col;//第二排皇后末尾位置列号
    int n;//棋盘规模
    int k;
public:
    Chessboard();
    void triangularNQueens(int N);//从规模k扩展棋盘到规模N
    string toString(int i, int N);
};
Chessboard::Chessboard(){
	x.push_back(0), x.push_back(-1), x.push_back(1);//初始三角形
    first_col=0;
    seconde_row=2;
    seconde_col=1;
	k=3;
    n=3;
}
void Chessboard::triangularNQueens(int N){
    n = N>n ? N : n;//修正棋盘规模
    while(k<n){//逐层扩展三角形
        switch (k%3) {
            case 0: //扩展右腰
				x.insert(x.begin(), 1, -1);
                seconde_row++;
                first_col+=2;
                x[first_col]=first_col;
	 	        break;//第一排皇后追加一个
            case 1: //扩展底边
                x.insert(x.begin()+seconde_row, 1, -1);//第二排皇后下沉一行
                seconde_row++;
				break;
            default: //扩展底边
                seconde_col+=2;//第二排皇后追加一个
                x.push_back(seconde_col);
            }
        k++;
    }
}
string Chessboard::toString(int i, int N){//返回第i个案例格局
	ostringstream s; 
    s<<(i+1)<<" "<<N<<" "<<((2*N+1)/3)<<endl;
    int count=0;
    for (int j=0; j<N; j++) {
        if (x[j] > -1) {
            s<<"["<<(j+1)<<", "<<(x[j]+1)<<"] ";
            if (++count == 8) {
                s<<endl;
            }
        }
    }
    s<<endl;
	return s.str();
}

int main(){
	ifstream inputdata("Triangular N-Queens/inputdata.txt");
    ofstream outputdata("Triangular N-Queens/outputdata.txt");
	int c;
	inputdata>>c;
	Chessboard chess;
	for (int i=0; i<c; i++){
		int n;
		inputdata>>n;
		chess.triangularNQueens(n);
		string s=chess.toString(i, n);
		outputdata<<s;
		cout<<s;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}