//
//  Internet Bandwidth.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include "../utility/maxflow.h"
struct Connect{
	int u, v, w;
	Connect(int a, int b, int c):u(a), v(b), w(c){}
};
pair<Network , vector<vector<int>>> makeGraph(vector<Connect> &connect, int n){
	Network g=Network(n);
	vector<vector<int>> c(n, vector<int>(n));
	int m=connect.size();
	for(int i=0; i<m; i++){
		int u=connect[i].u, v=connect[i].v, w=connect[i].w;
		g.insertEdge(u, v); g.insertEdge(v, u);
		c[u][v]=w; c[v][u]=w;
	}
	return make_pair(g, c);
}
int internetWidth(vector<Connect> &connect, int n, int s, int t){
	pair<Network, vector<vector<int>>> p=makeGraph(connect, n);
	Network G=p.first;
	vector<vector<int>> c=p.second;
	int result=maxFlow(G, c, s, t);
	return result;
}
int main(){
    ifstream inputdata("Internet Bandwidth/inputdata.txt");
    ofstream outputdata("Internet Bandwidth/outputdata.txt");
	int n, i=0;
	inputdata>>n;
	while(n>0){
		i++;
		int s, t, m;
		inputdata>>s>>t>>m;
		vector<Connect> connect;
		for(int k=0; k<m; k++){
			int u, v, x;
			inputdata>>u>>v>>x;
			connect.push_back(Connect(u-1, v-1, x));
		}
		int result=internetWidth(connect, n, s-1, t-1);
		outputdata<<"Network "<<i<<endl;
		outputdata<<"The bandwidth is "<<result<<"."<<endl;
		cout<<"Network "<<i<<endl;
		cout<<"The bandwidth is "<<result<<"."<<endl;
		inputdata>>n;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
