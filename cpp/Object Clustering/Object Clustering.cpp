//
//  Object Clustering.cpp
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
vector<int> mstPrim(vector<vector<int>> &w, int r){
	int n=w.size();
    vector<int> pi(n, -1);
	vector<int> key(n, INT_MAX);
    vector<bool> poped(n, false);
    key[r]=0;
    PriorityQueue<Key, greater<Key>> Q;
    for (int i=0; i<n; i++)
        Q.push(Key(i, key[i]));
    while(!Q.empty()){
		int u=Q.top().index;
        Q.pop();
        poped[u]=true;
        for (int v=0; v<n; v++)
            if (!poped[v])//若v在队列Q
                if (w[u][v] != 0)
                    if (w[u][v]<key[v]) {//w(u,v)<key[v]
                        pi[v]=u;
                        key[v]=w[u][v];
                        Key ele(v, key[v]);
                        int i=Q.search(ele);
						ele.weight=key[v];
                        Q.replace(ele, i);
                    }
    }
    return key;
}
int objectCluster(vector<pair<int, int>> &object, int k){
    int n=object.size();
    vector<vector<int>> W(n, vector<int>(n));
    for (int u=1; u<n; u++) {
		int x1=object[u].first, y1=object[u].second;
        for (int v=0; v<u; v++) {
			int x2=object[v].first, y2=object[v].second;
            int d=abs(x1-x2)+abs(y1-y2);
            W[u][v]=d; W[v][u]=d;
        }
    }
    vector<int> key=mstPrim(W, 0);
	sort(key.begin(), key.end(), greater<int>());
    return key[k-2];
}
int main(){
    ifstream inputdata("Object Clustering/inputdata.txt");
    ofstream outputdata("Object Clustering/outputdata.txt");
	int N, K;
	inputdata>>N>>K;
	vector<vector<int>> W(N, vector<int>(N));
	vector<pair<int, int>> object;
	for(int i=0; i<N; i++){
		int a, b;
		inputdata>>a>>b;
		object.push_back(make_pair(a, b));
	}
	int result=objectCluster(object, K);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close(), outputdata.close();
    return 0;
}