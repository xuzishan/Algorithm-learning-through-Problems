//
//  Network Safeguard.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/3/5.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "../utility/Graph.h"
struct edge{
    int end;
    int num;
    edge(int v, int n=0): end(v), num(n){}
};
bool operator==(const edge &a, const edge &b){
    return a.end==b.end;
}
class Network: public Graph<edge>{
    vector<Color> color;
    vector<int> d;
    vector<int> low;
    int time;
    int s;
public:
    vector<int> A1;
    Network(int n, int start):Graph<edge>(n), s(start),time(0) {
        color=vector<Color>(n, WHITE);
        d=vector<int>(n, 0);
        low=vector<int>(n, 0);
        A1=vector<int>();
    }
    void reset(){
        color=vector<Color>(scale, WHITE);
        d=vector<int>(scale, 0);
        low=vector<int>(scale, 0);
        A1=vector<int>();
        time=0;
    }
    void insertEdge(int u, int v, int w=0) {
		list<edge>::iterator i=find(A[u].begin(), A[u].end(), edge(v));
        if (i!=A[u].end()){
            (*i).num++;
            list<edge>::iterator j=find(A[v].begin(), A[v].end(), edge(u));
            (*j).num++;
            return;
        }
        A[u].push_back(edge(v, w));
    }
	void bridges(int u, int v){
		color[v]=GRAY;
		d[v] = ++time;
		low[v]=d[v];
		for (list<edge>::iterator i=A[v].begin(); i != A[v].end(); i++) {
			int t=(*i).end;
			if (color[t]==WHITE) {
				bridges(v, t);
				low[v]=min(low[v], low[t]);
				list<edge>::iterator p=find(A[v].begin(), A[v].end(), edge(t,0));
				if ((*p).num>0) {
					continue;
				}
				if (low[t]>=d[t]) {
					A1.push_back(v); A1.push_back(t);
				}
			}else if (color[t] == GRAY && t != u) {
				low[v]=min(low[v], d[t]);
			}
		}
		color[v]=BLACK;
	}
};
Network* makeGraph(vector<pair<int, int>> &connect, int N){
	int M=connect.size();
	Network* g=new Network(N, 0);
	for (int i=0; i<M; i++){
		int u=connect[i].first, v=connect[i].second;
		g->insertEdge(u, v);g->insertEdge(v, u);
	}
	return g;
}
vector<int> networkSafeguard(vector<pair<int, int>> &connect, vector<pair<int, int>> &newConnect, int N, int Q){
	Network* G=makeGraph(connect, N);
	vector<int> result;
	for (int i=0; i<Q; i++){
		int u=newConnect[i].first, v=newConnect[i].second;
		G->insertEdge(u, v);G->insertEdge(v, u);
		G->bridges(0, 0);
		int r=(G->A1.size())/2;
		result.push_back(r);
		G->reset();
	}
	delete G;
	return result;
}
int main(){
    ifstream inputdata("Network Safeguard/inputdata.txt");
    ofstream outputdata("Network Safeguard/outputdata.txt");
	int N, M, i=0;
	inputdata>>N>>M;
	while (N>0&&M>0){
		vector<pair<int, int>> connect;
		for (int i=0; i<M; i++){
			int A, B;
			inputdata>>A>>B;
			connect.push_back(make_pair(A-1, B-1));
		}
		int Q;
		inputdata>>Q;
		vector<pair<int, int>> newConnect;
		for(int i=0; i<Q; i++){
			int A, B;
			inputdata>>A>>B;
			newConnect.push_back(make_pair(A-1, B-1));
		}
		vector<int> result=networkSafeguard(connect, newConnect, N, Q);
		outputdata<<"Case "<<++i<<" : "<<endl;
		cout<<"Case "<<i<<" : "<<endl;
		for (int i=0; i<result.size(); i++){
			outputdata<<result[i]<<endl;
			cout<<result[i]<<endl;
		}
		inputdata>>N>>M;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
