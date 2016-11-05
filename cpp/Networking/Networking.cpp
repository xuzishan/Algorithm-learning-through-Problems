//
//  Networking.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/10/28.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "..\utility\PriorityQueue.h"
struct Key{
	int index, weight;
	Key(int x, int y):index(x), weight(y){}
};
bool operator>(const Key &a, const Key &b){
	return a.weight>b.weight;
}
bool operator==(const Key &a, const Key &b){
	return a.index==b.index;
}
int mstPrim(vector<vector<int>> &w, int r){
	int n=w.size();
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
                        key[v]=w[u][v];
                        Key ele(v, key[v]);
                        int i=Q.search(ele);
						ele.weight=key[v];
                        Q.replace(ele, i);
                    }
    }
    int weight=0;
    for (int i=0; i<n; i++)
        weight+=key[i];
    return weight;
}
int main(){
    ifstream inputdata("Networking/inputdata.txt");
    ofstream outputdata("Networking/outputdata.txt");
	int P;
	inputdata>>P;
	while(P){
		int R;
		inputdata>>R;
		if(!R){
			outputdata<<0<<endl;
			cout<<0<<endl;
			inputdata>>P;
			continue;
		}
		vector<vector<int>> W(P, vector<int>(P));
		for(int i=0; i<R; i++){
			int u, v, w;
			inputdata>>u>>v>>w;
			if(W[u-1][v-1]==0||W[u-1][v-1]>w){
				W[u-1][v-1]=w;
				W[v-1][u-1]=w;
			}
		}
		int weight=mstPrim(W, 0);
		outputdata<<weight<<endl;
		cout<<weight<<endl;
		inputdata>>P;
	}
    inputdata.close(), outputdata.close();
    return 0;
}