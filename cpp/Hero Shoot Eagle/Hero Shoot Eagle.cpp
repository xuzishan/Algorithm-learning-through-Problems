//
//  Hero Shoot Eagle.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/28.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
vector<vector<int>>  lcsLength(vector<int> &x, vector<int> &y){
	int m=x.size(), n=y.size();
    vector<vector<int>> c(m+1, vector<int>(n+1));
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++)
            if (x[i-1]==y[j-1])
				c[i][j]=c[i-1][j-1]+1;
            else
                c[i][j]=max(c[i-1][j], c[i][j-1]);
    return c;
}
void lcsSolution(vector<vector<int>> &c, vector<int> &x, vector<int> y, int i, int j, ostringstream &s){
    if (i == 0 || j == 0)
        return;
    if (x[i-1] == y[j-1]) {
        lcsSolution(c, x, y, i-1, j-1, s);
        s<<x[i-1]<<" ";
    }else if (c[i-1][j]<=c[i][j-1])
        lcsSolution(c, x, y, i, j-1, s);
    else
        lcsSolution(c, x, y, i-1, j, s);
}
string heroShootEagle(vector<int> &a){
	int n=a.size();
    vector<int> b(a);
	sort(b.begin(), b.end(), greater<int>());
    vector<vector<int>> c=lcsLength(a, b);
    ostringstream s;
	s<<(c[n][n])<<endl;
    lcsSolution(c, a, b, n, n, s);
    return s.str();
}
int main(){
    ifstream inputdata("Hero Shoot Eagle/inputdata.txt");
    ofstream outputdata("Hero Shoot Eagle/outputdata.txt");
	int n;
	while(inputdata>>n){
		vector<int> a(n);
		for(int i=0; i<n; i++)
			inputdata>>a[i];
		string result=heroShootEagle(a);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();outputdata.close();
    return 0;
}