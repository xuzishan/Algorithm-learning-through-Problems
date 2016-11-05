//
//  Selecting Courses.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include "../utility/maxflow.h"
pair<Network , vector<vector<int>>> makeGraph(vector<vector<pair<int, int>>> &course){
	int n=course.size(), N=n+86;
    Network G(N);
    vector<vector<int>> c(N, vector<int>(N));
    for (int l=1; l<=n; l++) {
        G.insertEdge(0, l);
        c[0][l]=1;
    }
    for (int l=1; l<=n; l++) {
        int t=course[l-1].size();
        for (int j=0; j<t; j++){
			int p=course[l-1][j].first, q=course[l-1][j].second;
            int r=n+(p-1)*12+q;
            G.insertEdge(l, r);
            c[l][r]=1;
        }
    }
    for (int r=n+1; r<N-1; r++) {
        G.insertEdge(r, N-1);
        c[r][N-1]=1;
    }
    return make_pair(G, c);
}
int selectingCourse(vector<vector<pair<int, int>>> &course) {
	int n=course.size(), N=n+86;
    pair<Network, vector<vector<int>>> p=makeGraph(course);
	Network G=p.first;
	vector<vector<int>> c=p.second;
    int f=maxFlow(G, c, 0, N-1);
    return f;
}
int main(){
    ifstream inputdata("Selecting Courses/inputdata.txt");
    ofstream outputdata("Selecting Courses/outputdata.txt");
	int n;
	while(inputdata>>n){
		vector<vector<pair<int, int>>> course(n, vector<pair<int, int>>());
		for(int i=0; i<n; i++){
			int t;
			inputdata>>t;
			for(int j=0; j<t; j++){
				int p, q;
				inputdata>>p>>q;
				course[i].push_back(make_pair(p, q));
			}
		}
		int result=selectingCourse(course);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
	inputdata.close();
	outputdata.close();
    return 0;
}