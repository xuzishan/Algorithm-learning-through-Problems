//
//  Bonnie and Clyde.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/3/5.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include "../utility/Graph.h"
class Network: public Graph<int>{
    vector<Color> color;
    vector<int> d;
    vector<int> low;
	vector<int> lp;
    int time;
    int s;
	bool flag;
public:
    vector<int> A1;
    Network(int n, int start):Graph<int>(n), s(start),time(0), flag(false) {
        color=vector<Color>(n, WHITE);
        d=vector<int>(n, 0);
        low=vector<int>(n, 0);
        A1=vector<int>();
		lp=vector<int>(n);
		lp[0]=s;
    }
    void artpoints(int u){
        color[u]=GRAY;
        d[u] = ++time;
        low[u]=d[u];
        int rootdegree=0;
        bool artpoint=false;
		for (list<int>::iterator i=A[u].begin(); i != A[u].end(); i++) {
            int v=(*i);
            if (color[v]==WHITE) {
                artpoints(v);
                if (u==s) {
                    rootdegree++;
                    if (rootdegree==2) {
                        artpoint=true;
                    }
                }else{
                    low[u]=min(low[u], low[v]);
                    if (low[v] == d[u]) {
                        artpoint=true;
                    }
                }
            } else if (color[v] == GRAY) {
                low[u]=min(low[u], d[v]);
            }
        }
        if (artpoint) {
            A1.push_back(u);
        }
        color[u]=BLACK;
    }
    void reset(){
        color=vector<Color>(scale, WHITE);
        d=vector<int>(scale, 0);
        low=vector<int>(scale, 0);
        time=0;
        A1=vector<int>();
    }
    void loopPath(int k){
        int n=A.size();
        if (k>=n)
            if (find(A[lp[n-1]].begin(), A[lp[n-1]].end(), lp[0]) != A[lp[n-1]].end()) {
                flag=true;
                return;
            }
        int u=lp[k-1];
		for (list<int>::iterator i=A[u].begin(); i != A[u].end(); i++)
            if (!flag) {
                int v=*i;
                if (color[v] == WHITE) {
                    color[v]=GRAY;
                    lp[k]=v;
                    loopPath(k+1);
                    color[v]=WHITE;
                }
            }
    }
    int bonnieAndClyde(){
		int n=A.size();
        int ways=0;
        artpoints(s);
        if (!A1.empty()) {
            for (int i=1; i<=A1.size(); i++) {
                ways+=(n-i);
            }
            return ways;
        }
		reset();color[0]=GRAY;
        loopPath(1);
        for (int i=0; i<n-2; i++) {
			int m=min(i+n-2, n-1);
            for (int j=i+2; j<=m; j++) {
				list<int> &S1=A[lp[j-1]];
				list<int> S2;
                if (j<n-1) {
                    S2=list<int>(lp.begin()+j+1, lp.begin()+n);
                }
                if (i>0) {
					S2.insert(S2.end(), lp.begin(), lp.begin()+i);
                }
				list<int> S3;
				set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), S3.begin());
				if (S3.empty()) {
                    ways++;
                }
            }
        }
        return ways;
    }
};
Network makeGraph(vector<pair<int, int>> &connect, int N){
	int M=connect.size();
	Network g(N, 0);
	for (int i=0; i<M; i++){
		int u=connect[i].first, v=connect[i].second;
		g.insertEdge(u, v);g.insertEdge(v, u);
	}
	return g;
}
int main(){
    ifstream inputdata("Bonnie and Clyde/inputdata.txt");
    ofstream outputdata("Bonnie and Clyde/outputdata.txt");
	int N, M, i=1;
	inputdata>>N>>M;
	while(N>0&&M>0){
		vector<pair<int, int>> connect;
		for(int i=0; i<M; i++){
			int A, B;
			inputdata>>A>>B;
			connect.push_back(make_pair(A-1, B-1));
		}
		Network G=makeGraph(connect, N);
		int result=G.bonnieAndClyde();
		outputdata<<"Case "<<i<<": "<<result<<endl;
		cout<<"Case "<<i++<<": "<<result<<endl;
		inputdata>>N>>M;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
