//
//  maxflow.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include "maxflow.h"
Network::Network(int n): Graph<int>(n){
    color=vector<Color>(n, WHITE);
    d=vector<int>(n, INT_MAX);
    pi=vector<int>(n, -1);
}
void Network::reset(){
    color=vector<Color>(scale, WHITE);
    d=vector<int>(scale, INT_MAX);
    pi=vector<int>(scale, -1);
}
void Network::bfsVisit(int s){
	queue<int> Q;
	color[s]=GRAY;
	d[s]=0;
	Q.push(s);
	while (!Q.empty()) {
		int u=Q.front(); Q.pop();
		for (list<int>::iterator i=A[u].begin(); i != A[u].end() ; i++) {
			int v=*i;
			if (color[v]==WHITE) {
				d[v]=d[u]+1;
				pi[v]=u;
				color[v]=GRAY;
				Q.push(v);
			}
		}
		color[u]=BLACK;
	}
}
int maxFlow(Network &G, vector<vector<int>> &c, int s, int t){
	int n=G.size();
    vector<vector<int>> f(n, vector<int>(n));
    G.bfsVisit(s);
    while (G.d[t] < INT_MAX) {
        vector<pair<int, int>> p;
        int v=t, u=G.pi[v];
        while (u > -1) {
            p.push_back(make_pair(u, v));
            v=u;
            u=G.pi[v];
        }
        int cp=INT_MAX;
		for (int i=0; i<p.size(); i++) {
			if (c[p[i].first][p[i].second]<cp) {
				cp=c[p[i].first][p[i].second];
            }
        }
		for (int i=0; i<p.size(); i++) {
			int u=p[i].first, v=p[i].second;
            f[u][v]+=cp;
            f[v][u] = -f[u][v];
            c[u][v]-=cp;
            if (c[u][v]==0) {
                G.deleteEdge(u, v);
            }
			if (c[v][u]==0 && find(G.A[v].begin(), G.A[v].end(), u) == G.A[v].end()) {
                G.insertEdge(v, u);
            }
            c[v][u]+=cp;
        }
        G.reset();
        G.bfsVisit(s);
    }
    int maxf=0;
    for (int i=0; i<n; i++) {
        maxf+=f[s][i];
    }
    return maxf;
}
