//
//  Happy Travel.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/28.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
vector<vector<int>> knapsak(vector<int> &v, vector<int> &w, int C){
	int n=v.size();
    vector<vector<int>> m(n+1, vector<int>(C+1));
    for (int i=1; i<=n; i++)
        for (int j=1; j<=C; j++) {
            m[i][j]=m[i-1][j];
            if (w[i-1]<=j)
                if (v[i-1]+m[i-1][j-w[i-1]]>m[i-1][j])
                    m[i][j]=v[i-1]+m[i-1][j-w[i-1]];
        }
    return m;
}
pair<int, int> happyTravel(vector<int> &w){
	int n=w.size();
    int W=0;
    for (int i=0;  i<n; i++)
        W+=w[i];
    int C=W/2;
    vector<int> v(w);
    vector<vector<int>> m=knapsak(v, w, C);
    int x=m[n][C];
	int y=W-x;
    return make_pair(x, y);
}
int main(){
    ifstream inputdata("Happy Travel/inputdata.txt");
    ofstream outputdata("Happy Travel/outputdata.txt");
	int N, num=1;
	while(inputdata>>N){
		vector<int> w(N);
		for (int i=0; i<N; i++)
			inputdata>>w[i];
		pair<int, int> result=happyTravel(w);
		outputdata<<"Case "<<num<<": "<<result.first<<" "<<result.second<<endl;
		cout<<"Case "<<num++<<": "<<result.first<<" "<<result.second<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}