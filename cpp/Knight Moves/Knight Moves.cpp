//
//  Knight Moves.cpp
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
class Board: public Graph<int>{
public:
	vector<int> d;
	vector<Color> color;
	Board(int n): Graph<int>(n){
		d=vector<int>(n, 0);
		color=vector<Color>(n, WHITE);
	}
};
Board* makeGraph(int l){
	Board *g=new Board(l*l);
    for (int i=0; i<l; i++) {
        for (int j=0; j<l; j++) {
            int u=i*l+j;
            if (i>=1) {
                if (j>=2) {
                    int v=(i-1)*l+j-2;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
                if (j<l-2) {
                    int v=(i-1)*l+j+2;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
            }
            if (i>=2) {
                if (j>=1) {
                    int v=(i-2)*l+j-1;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
                if (j<l-1) {
                    int v=(i-2)*l+j+1;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
            }
            if (i<l-1) {
                if (j>=2) {
                    int v=(i+1)*l+j-2;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
               }
                if (j<l-2) {
                    int v=(i+1)*l+j+2;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
            }
            if (i<l-2) {
                if (j>=1) {
                    int v=(i+2)*l+j-1;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
                if (j<l-1) {
                    int v=(i+2)*l+j+1;
                    g->insertEdge(u, v);
                    g->insertEdge(v, u);
                }
            }
        }
    }
	return g;
}
int bfsVisit(Board* G, int s, int t){
    queue<int> Q;
    int count=0;
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
int knightMoves(int l, pair<int, int> p1, pair<int, int> p2){
	if(p1==p2)
		return 0;
    Board* G=makeGraph(l);
	int x=p1.first, y=p1.second;
    int s=x*l+y;
	x=p2.first, y=p2.second;
    int t=x*l+y;
	int r=bfsVisit(G, s, t);
	delete G;
    return r;
}
int main(){
    ifstream inputdata("Knight Moves/inputdata.txt");
    ofstream outputdata("Knight Moves/outputdata.txt");
	int n;
	inputdata>>n;
	for(int i=0; i<n; i++){
		int l, r, c;
		inputdata>>l;
		inputdata>>r>>c;
		pair<int, int> p1(r, c);
		inputdata>>r>>c;
		pair<int, int> p2(r, c);
		int result=knightMoves(l, p1, p2);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
