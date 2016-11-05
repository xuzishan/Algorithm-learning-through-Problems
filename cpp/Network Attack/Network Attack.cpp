//
//  Network Attack.cpp.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/3/5.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
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
Network makeGraph(vector<pair<int, int>> &connect, vector<pair<int, int>> &newConnect){
	int N=connect.size()+1, M=newConnect.size();
	Network G(N, 0);
	for (int i=0; i<N-1; i++){
		int u=connect[i].first, v=connect[i].second;
		G.insertEdge(u, v); G.insertEdge(v, u);
	}
	for (int i=0; i<M; i++){
		int u=newConnect[i].first, v=newConnect[i].second;
		G.insertEdge(u, v); G.insertEdge(v, u);
	}
	return G;
}
int networkAttach(vector<pair<int, int>> &connect, vector<pair<int, int>> &newConnect){
	Network g=makeGraph(connect, newConnect);
	int sum=0;
	for (int i=0; i<newConnect.size(); i++){
		Network G(g); 
		int u=newConnect[i].first, v=newConnect[i].second;
		G.deleteEdge(u, v); G.deleteEdge(v, u);
		G.bridges(0, 0);
		for(int j=0; j<G.A1.size(); j+=2){
			int u=G.A1[j], v=G.A1[j+1];
			if (find(newConnect.begin(), newConnect.end(), make_pair(u, v))==newConnect.end()||
				find(newConnect.begin(), newConnect.end(), make_pair(v, u))==newConnect.end())
				sum++;
		}
	}
	return sum;
}
int main(){
    ifstream inputdata("Network Attack/inputdata.txt");
    ofstream outputdata("Network Attack/outputdata.txt");
	int N, M;
	inputdata>>N>>M;
	vector<pair<int, int>> connect, newConnect;
	for(int i=0; i<N-1; i++){
		int u, v;
		inputdata>>u>>v;
		connect.push_back(make_pair(u-1, v-1));
	}
	for(int i=0; i<M; i++){
		int u, v;
		inputdata>>u>>v;
		newConnect.push_back(make_pair(u-1, v-1));
	}
	int result=networkAttach(connect, newConnect);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
