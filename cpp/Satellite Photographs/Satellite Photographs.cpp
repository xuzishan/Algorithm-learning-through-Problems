//
//  Satellite Photographs.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/2/27.
//  Copyright (c) 2016Äê xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "../utility/Graph.h"
class Photograph: public Graph<int>{
public:
	vector<Color> color;
	Photograph(int n):Graph(n){
		color=vector<Color>(n, WHITE);
	}
};
int bfsVisit(Photograph &G, int s){
    queue<int> Q;
    int count=0;
    G.color[s]=GRAY;
    Q.push(s);
    while (!Q.empty()) {
        int u=Q.front(); Q.pop();
		count++;
		for (list<int>::iterator i=G.A[u].begin(); i != G.A[u].end() ; i++) {
            int v=*i;
            if (G.color[v]==WHITE) {
                G.color[v]=GRAY;
                Q.push(v);
            }
        }
        G.color[u]=BLACK;
    }
    return count;
}
Photograph* makeGraph(vector<string> &photograph){
    vector<pair<int, int>> p;
	int H=photograph.size(), W=photograph[0].length();
    for (int i=0; i<H; i++) {
        for (int j=0; j<W; j++) {
            if (photograph[i][j]=='*'){
                p.push_back(make_pair(i, j));
            }
        }
    }
	int n=p.size();
    Photograph* g=new Photograph(n);
    for (int i=1; i<n; i++) {
		int xi=p[i].first, yi=p[i].second;
        for (int j=0; j<i; j++) {
			int xj=p[j].first, yj=p[j].second;
            if ((xi==xj && yi==yj+1)||(xi==xj+1 && yi==yj)){
                g->insertEdge(i, j);
                g->insertEdge(j, i);
            }
        }
    }
    return g;
}
int satellitePhotographs(Photograph &G){
    int max=0;
    for (int s=0; s<G.scale; s++) {
        if (G.color[s]==WHITE) {
            int x=bfsVisit(G, s);
            if (max<x)
                max=x;
        }
    }
    return max;
}
int main(){
    ifstream inputdata("Satellite Photographs/inputdata.txt");
    ofstream outputdata("Satellite Photographs/outputdata.txt");
	int w, h;
	inputdata>>w>>h;
	vector<string> photograph;
	for(int i=0; i<h; i++){
		string s;
		inputdata>>s;
		photograph.push_back(s);
	}
	Photograph *G=makeGraph(photograph);
	int result=satellitePhotographs(*G);
	outputdata<<result<<endl;
	cout<<result<<endl;
	delete G;
    inputdata.close();
	outputdata.close();
    return 0;
}
