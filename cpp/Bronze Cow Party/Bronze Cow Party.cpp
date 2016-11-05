//
//  Bronze Cow Party.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/10/28.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#include "..\utility\PriorityQueue.h"
struct Key{
	int index;
	int weight;
	Key(int x, int y):index(x), weight(y){}
};
bool operator>(const Key &a, const Key &b){
	return a.weight>b.weight;
}
bool operator==(const Key &a, const Key &b){
	return a.index==b.index;
}
struct Road{
	int a, b, t;
	Road(int x, int y, int z):a(x), b(y), t(z){}
};
vector<int> dijkstra(vector<vector<int>> &W, int s){
	int n=W.size();
    vector<int> d(n, INT_MAX);
    vector<bool> poped(n, false);
    d[s]=0;
    PriorityQueue<Key, greater<Key>> Q;
    for (int i=0;i<n; i++) {
        Q.push(Key(i, d[i]));
    }
    while (!Q.empty()) {
		int u=Q.top().index; Q.pop();
        poped[u]=true;
        for (int v=0; v<n; v++)
            if (!poped[v])
                if (W[u][v]<INT_MAX)
                    if (d[v] > d[u]+W[u][v]){
                        d[v]=d[u]+W[u][v];
						Key ele(v, d[v]);
                        int i=Q.search(ele);
						ele.weight=d[v];
                        Q.replace(ele, i);
                    }
    }
    return d;
}
int bronzeCowParty(vector<Road> &roads, int N, int X) {
    vector<vector<int>> W(N, vector<int>(N, INT_MAX));
	int M=roads.size();
    for (int i=0; i<M; i++) {
		int u=roads[i].a, v=roads[i].b, w=roads[i].t;
        if (W[u-1][v-1]>w) {
            W[u-1][v-1]=w;
            W[v-1][u-1]=w;
        }
    }
    vector<int> d=dijkstra(W, X-1);
    int x=*(max_element(d.begin(), d.end()));
    return 2*x;
}
int main(){
    ifstream inputdata("Bronze Cow Party/inputdata.txt");
    ofstream outputdata("Bronze Cow Party/outputdata.txt");
	int N, M, X;
	inputdata>>N>>M>>X;
	vector<Road> roads;
	for(int i=0; i<M; i++){
		int a, b, t;
		inputdata>>a>>b>>t;
		roads.push_back(Road(a, b, t));
	}
	int result=bronzeCowParty(roads, N, X);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close(), outputdata.close();
    return 0;
}