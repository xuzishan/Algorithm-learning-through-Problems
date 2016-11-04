//
//  Cleaning Robot.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 15/5/24.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Yard{
    vector<vector<int>> grid;
    int gn;
    int m, n;
public:
    Yard(vector<pair<int, int>> &a, int rows, int colums){
		gn = a.size();
        m = rows;
        n = colums;
        grid = vector<vector<int>>(m, vector<int>(n));
		for (vector<pair<int, int>>::iterator p=a.begin(); p!=a.end(); p++)
			grid[p->first-1][p->second-1]=1;
    }
    void oneRobot(){
        vector<vector<int>> b(m, vector<int>(n));
        vector<vector<int>> c(m+1, vector<int>(n+1));
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=n; j++) {
                int q;
                if (c[i-1][j] >= c[i][j-1]) {
                    q=c[i-1][j];
                    b[i-1][j-1]=1;
                }else
                    q=c[i][j-1];
                c[i][j]=q+grid[i-1][j-1];
            }
        }
        int i=m-1, j=n-1;
        while (i>=0 && j>=0) {
            if (grid[i][j]==1) {
                grid[i][j]=0;
                gn--;
            }
            if (b[i][j]==1)
                i--;
            else
                j--;
        }
    }
    int cleaningRobots(){
        int count=0;
        while (gn>0) {
            oneRobot();
            count++;
        }
        return count;
    }
};

int main(){
	ifstream inputdata("Cleaning Robot/inputdata.txt");
	ofstream outputdata("Cleaning Robot/outputdata.txt");
	int x, y;
	inputdata>>x>>y;
	while (x>-1&&y>-1) {
		int m=0, n=0;
		vector<pair<int, int>> a;
		while(x>0||y>0){
			m=x>m?x:m;
			n=y>n?y:n;
			a.push_back(make_pair(x, y));
			inputdata>>x>>y;
		}
		Yard A(a, m, n);
		int rn=A.cleaningRobots();
		outputdata<<rn<<endl;
		cout<<rn<<endl;
		inputdata>>x>>y;
	}
	inputdata.close();outputdata.close();
	return 0;
}
