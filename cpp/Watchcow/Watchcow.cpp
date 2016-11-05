//
//  Watchcow.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/2/27.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "../utility/Graph.h"
class Farm: public Graph<int>{
public:
    vector<Color> color;
    vector<int> pi;
    vector<int> patrolPath;
    Farm (int n): Graph(n){
        color=vector<Color>(n, WHITE);
        pi=vector<int>(n, -1);
        patrolPath=vector<int>();
    }
	void dfsVisit(int u){
		color[u]=GRAY;
		patrolPath.push_back(u+1);
		list<int>::iterator i=A[u].begin();
		while ( i != A[u].end()) {
			int v=*i;
			if (color[v]==WHITE) {
				pi[v]=u;
				dfsVisit(v);
				patrolPath.push_back(u+1);
				i++;
				deleteEdge(u, v);
				deleteEdge(v, u);
			}else if (v != pi[u]) {
				i++;
				patrolPath.push_back(v+1);
				patrolPath.push_back(u+1);
				deleteEdge(u, v);
				deleteEdge(v, u);
			}else
				i++;
		}
		color[u]=BLACK;
	}
};
Farm makeGraph(vector<pair<int, int>> &road, int N){
    Farm G(N);
	for (int i=0; i<road.size(); i++) {
		int u=road[i].first, v=road[i].second;
        G.insertEdge(u, v);
        G.insertEdge(v, u);
    }
    return G;
}
string watchCow(vector<pair<int, int>> &road, int N){
    Farm G=makeGraph(road, N);
    G.dfsVisit(0);
    ostringstream s;
	copy(G.patrolPath.begin(), G.patrolPath.end(), ostream_iterator<int>(s, " "));
    return s.str();
}

int main(){
    ifstream inputdata("Watchcow/inputdata.txt");
    ofstream outputdata("Watchcow/outputdata.txt");
	int n, m;
	inputdata>>n>>m;
	vector<pair<int, int>> road;
	for(int i=0; i<m; i++){
		int u, v;
		inputdata>>u>>v;
		road.push_back(make_pair(u-1, v-1));
	}
	string result=watchCow(road, n);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
