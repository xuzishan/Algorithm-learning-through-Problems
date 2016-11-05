//
//  Dining.cpp.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include "../utility/maxflow.h"
pair<Network, vector<vector<int>>> makeGraph(int F, int D, vector<vector<int>> &u, vector<vector<int>> &v, vector<int> &f, vector<int> &d){
	int N=u.size();
	Network G(F+D+2);
	vector<vector<int>> c(F+D+2,vector<int>(F+D+2));
	for (int v=1; v<=F; v++) {
		G.insertEdge(0, v);
		c[0][v]=1;
	}
	for (int u=F+1; u<=F+D; u++) {
		G.insertEdge(u, F+D+1);
		c[u][F+D+1]=1;
	}
	for (int i=0; i<N; i++){
		for (int p=0; p<f[i]; p++) {
			for (int q=0; q<d[i]; q++) {
				G.insertEdge(u[i][p], v[i][q]+F);
				c[u[i][p]][v[i][q]+F]=1;
			}
		}
	}
	return make_pair(G, c);
}
int dining(int F, int D, vector<vector<int>> &u, vector<vector<int>> &v, vector<int> &f, vector<int> &d){
	pair<Network, vector<vector<int>>> r=makeGraph(F, D, u, v, f, d);
	Network G=r.first;
	vector<vector<int>> c=r.second;
	int result=maxFlow(G, c, 0, F+D+1);
	return result;
}
int main(){
    ifstream inputdata("Dining/inputdata.txt");
    ofstream outputdata("Dining/outputdata.txt");
	int N, F, D;
	inputdata>>N>>F>>D;
	vector<vector<int>> u(N, vector<int>());
	vector<vector<int>> v(N, vector<int>());
	vector<int> f(N), d(N);
	for (int i=0; i<N; i++){
		inputdata>>f[i]>>d[i];
		for (int j=0; j<f[i]; j++){
			int x;
			inputdata>>x;
			u[i].push_back(x);
		}
		for (int j=0; j<d[i]; j++){
			int x;
			inputdata>>x;
			v[i].push_back(x);
		}
	}
	int result=dining(F, D, u, v, f, d);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
