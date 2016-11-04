//
//  Pages Cluster.cpp
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
	double weight;
	Key(int x, double y):index(x), weight(y){}
};
bool operator>(const Key &a, const Key &b){
	return a.weight>b.weight;
}
bool operator==(const Key &a, const Key &b){
	return a.index==b.index;
}
struct Page{
	double x, y, z;
	Page(double a, double b, double c):x(a), y(b), z(c){}
};
vector<double> mstPrim(vector<vector<double>> &w, int r){
	int n=w.size();
    vector<int> pi(n, -1);
	vector<double> key(n, DBL_MAX);
    vector<bool> poped(n, false);
    key[r]=0.0;
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
double pageCluster(vector<Page> &pages, int k){
    int n=pages.size();
    vector<vector<double>> W(n, vector<double>(n, 0.0));
    for (int u=1; u<n; u++) {
		double x1=pages[u].x, y1=pages[u].y, z1=pages[u].z;
        for (int v=0; v<u; v++) {
			double x2=pages[v].x, y2=pages[v].y, z2=pages[v].z;
            double s=(x1-x2)*(x1-x2), t=(y1-y2)*(y1-y2),w=(z1-z2)*(z1-z2);
            double d=s+t+w;
            W[u][v]=d; W[v][u]=d;
        }
    }
    vector<double> key=mstPrim(W, 0);
	sort(key.begin(), key.end(), greater<double>());
    return key[k-2];
}

int main(){
    ifstream inputdata("Pages Cluster/inputdata.txt");
    ofstream outputdata("Pages Cluster/outputdata.txt");
	int n, k;
	inputdata>>n>>k;
	vector<Page> pages;
	for(int i=0; i<n; i++){
		double x, y, z;
		inputdata>>x>>y>>z;
		pages.push_back(Page(x, y, z));
	}
	double result=pageCluster(pages, k);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close(), outputdata.close();
    return 0;
}