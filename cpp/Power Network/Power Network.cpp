//
//  Power Network.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../utility/maxflow.h"
struct Line{
	int u, v, z;
	Line(int a, int b, int c): u(a), v(b), z(c){}
};
pair<Network* , vector<vector<int>>> makeGraph(vector<Line> &line, vector<pair<int, int>> &power, vector<pair<int, int>> &consummer, int n){
    Network* G= new Network(n+2);
    vector<vector<int>> c(n+2, vector<int>(n+2));
    int m=line.size();
    for (int i=0; i<m; i++) {
		int u=line[i].u, v=line[i].v, z=line[i].z;
        G->insertEdge(u, v);
        c[u][v]=z;
    }
    int np=power.size();
    for (int i=0; i<np; i++) {
		int u=power[i].first, z=power[i].second;
        G->insertEdge(n, u);
        c[n][u]=z;
    }
    int nc=consummer.size();
    for (int i=0; i<nc; i++) {
		int u=consummer[i].first, z=consummer[i].second;
        G->insertEdge(u, n+1);
        c[u][n+1]=z;
    }
    return make_pair(G, c);
}
int powerNetwork(vector<Line> &line, vector<pair<int, int>> &power, vector<pair<int, int>> &consummer, int n){
    pair<Network*, vector<vector<int>>> p=makeGraph(line, power, consummer, n);
	Network* G=p.first;
	vector<vector<int>> c=p.second;
    int f=maxFlow(G, c, n, n+1);
    return f;
}

int main(){
    ifstream inputdata("Power Network/inputdata.txt");
    ofstream outputdata("Power Network/outputdata.txt");
	int n;
	while(inputdata>>n){
		int np, nc, m;
		inputdata>>np>>nc>>m;
		vector<Line> line;
		for (int i=0; i<m; i++) {
			string s;
			inputdata>>s;
			s=s.substr(1);
			s.replace(s.find(',',0), 1, 1, ' ');
			s.replace(s.find(')',0), 1, 1, ' ');
			istringstream scanner(s);
			int u, v, z;
			scanner>>u>>v>>z;
			line.push_back(Line(u, v, z));
		}
		vector<pair<int, int>> power;
		for(int i=0; i<np; i++){
			string s;
			inputdata>>s;
			s=s.substr(1);
			s.replace(s.find(')',0), 1, 1, ' ');
			istringstream scanner(s);
			int u, z;
			scanner>>u>>z;
			power.push_back(make_pair(u, z));
		}
		vector<pair<int, int>> consummer;
		for(int i=0; i<nc; i++){
			string s;
			inputdata>>s;
			s=s.substr(1);
			s.replace(s.find(')',0), 1, 1, ' ');
			istringstream scanner(s);
			int u, z;
			scanner>>u>>z;
			consummer.push_back(make_pair(u, z));
		}
		int result=powerNetwork(line, power, consummer, n);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}