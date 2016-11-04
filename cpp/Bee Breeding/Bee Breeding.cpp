//
//  Bee Breeding.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/2/27.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "../utility/Graph.h"
class Honeycomb: public Graph<int>{
public:
	vector<int> d;
	vector<Color> color;
	Honeycomb(int n): Graph<int>(n){
		d=vector<int>(n, 0);
		color=vector<Color>(n, WHITE);
	}
};
Honeycomb* makeGraph(int n){
    int level=0, s=1;
    do{
        level++;
        s+=(level*6);
    }while (s<n);
    Honeycomb *g=new Honeycomb(1+3*level*(level+1));
    for (int u=1; u<7; u++) {
        int v=0;
        g->insertEdge(u,v);
        g->insertEdge(v,u);
        v = u+1 < 7 ? u+1 : 1;
        g->insertEdge(u,v);
        g->insertEdge(v,u);
    }
    for (int k=2; k<=level; k++) {
        int u=1+3*k*(k-1),v=1+3*(k-1)*(k-2),m=3*k*(k+1);
        g->insertEdge(u,v); g->insertEdge(v,u);
        g->insertEdge(u,u-1); g->insertEdge(u-1,u);
        u++; s=1;
        while(u<m){
            g->insertEdge(u,v); g->insertEdge(v,u);
            g->insertEdge(u,u-1); g->insertEdge(u-1,u);
            if (s++ % k != k-1) {
                v++;
                g->insertEdge(u,v); g->insertEdge(v,u);
            }
            u++;
        }
        g->insertEdge(u,u-1); g->insertEdge(u-1,u);
        g->insertEdge(u,v); g->insertEdge(v,u);
        g->insertEdge(u,++v); g->insertEdge(v, u);
    }
    return g;
}
int bfsVisit(Honeycomb* G, int s, int t){
    queue<int> Q;
    G->color[s]=GRAY;
    Q.push(s);
    while (!Q.empty()) {
        int u=Q.front(); Q.pop();
		for (list<int>::iterator i=G->A[u].begin(); i != G->A[u].end() ; i++) {
            int v=*i;
            if (G->color[v]==WHITE) {
                G->d[v]=G->d[u]+1;
                if (v==t)
                    return G->d[v];
                G->color[v]=GRAY;
                Q.push(v);
            }
        }
        G->color[u]=BLACK;
    }
    return 0;
}
int beeBreeding(int D, int E){
	if(D==E)
		return 0;
    int n=max(D, E);
    Honeycomb* G=makeGraph(n);
	int r=bfsVisit(G, D-1, E-1);
	delete G;
    return r;
}
int main(){
    ifstream inputdata("Bee Breeding/inputdata.txt");
    ofstream outputdata("Bee Breeding/outputdata.txt");
	int d, e;
	inputdata>>d>>e;
	while(d>0||e>0){
		int result=beeBreeding(d, e);
		outputdata<<"The distance between cells "<<d<<" to "<<e<<" is "<<result<<".\n";
		cout<<"The distance between cells "<<d<<" to "<<e<<" is "<<result<<".\n";
		inputdata>>d>>e;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
