//
//  The Shortest Path.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 15/5/23.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
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
struct FootPath{
	int u, v, w;
	FootPath(int a, int b, int c):u(a), v(b), w(c){}
};
struct Road{
	vector<int> p, d, t;
	Road(vector<int> &a, vector<int> &b, vector<int> &c):p(a), d(b), t(c){}
};
vector<vector<vector<Key>>> makeWeightMatrix(vector<FootPath> &footpath, vector<Road> &road, int N){
    vector<vector<vector<Key>>> W(N, vector<vector<Key>>(N));
    int M=footpath.size();
    for (int i=0; i<M; i++) {
		int u=footpath[i].u, v=footpath[i].v, w=footpath[i].w;
        W[u][v].push_back(Key(-1, w));
        W[v][u].push_back(Key(-1, w));
    }
	int K=road.size();
    for (int i=0; i<K; i++) {
		vector<int> p=road[i].p, d=road[i].d, t=road[i].t;
        int h=p.size();
        int k=t.size();
        for (int j=0; j<k; j++) {
            int currentTime=t[j];
            for (int x=0; x<h-1; x++) {
                int time=currentTime, length=d[x];
                int u=p[x], v=p[x+1];
                W[u][v].push_back(Key(time, length));
                currentTime+=d[x];
            }
            int u=p[h-1], v=p[0];
            int time=currentTime, length=d[h-1];
            W[u][v].push_back(Key(time, length));
        }
    }
    return W;
}
int wallk(vector<Key> &a){
    int i=0;
	while (i<a.size() && a[i].index != -1) {
        i++;
    }
	if (i<a.size())
        return i;
    return -1;
}
int ride(vector<Key> &a, int t) {
    int min=INT_MAX;
    int i=0, j=-1;
    while (i<a.size()) {
        if (a[i].index>=t && a[i].index-t < min) {
            min=a[i].index-t;
            j=i;
        }
        i++;
    }
    return j;
}
vector<int> dijkstra(vector<vector<vector<Key>>> &W, int A, int S){
	int n=W.size();
    vector<int> d(n, INT_MAX);
    vector<bool> poped(n, false);
    d[A]=0;
    PriorityQueue<Key, greater<Key>> Q;
    for (int i=0; i<n; i++)
        Q.push(Key(i, d[i]));
    while (!Q.empty()) {
		int da=Q.top().weight, u=Q.top().index; Q.pop();
        poped[u]=true;
        if (da<INT_MAX){
            int time=da+S;
            for (int v=0; v<n; v++)
                if (!poped[v]) {
					if (!W[u][v].empty()) {
                        int w1=INT_MAX;
                        int i=wallk(W[u][v]);
                        if (i > -1)
							w1=W[u][v][i].weight;
                        int w2=INT_MAX;
						int j=ride(W[u][v], time);
                        if (j>-1) {
							int t=W[u][v][j].index, l=W[u][v][j].weight;
                            w2=l+t-time;
                        }
                        int w=min(w1, w2);
                        if (w<INT_MAX)
                            if (d[v] > d[u]+w) {
                                d[v]=d[u]+w;
								Key ele=Key(v, d[v]);
                                int i=Q.search(ele);
								ele.weight=d[v];
                                Q.replace(ele, i);
                            }
                    }
                }
        }
    }
    return d;
}
vector<int> theShortestPath(vector<FootPath> &footpath, vector<Road> &road, int N, int A, int S) {
    vector<vector<vector<Key>>> W=makeWeightMatrix(footpath, road, N);
    vector<int> d=dijkstra(W, A, S);
    for (int i=0; i<N; i++) {
        if (d[i] == INT_MAX) {
            d[i] = -1;
        }
    }
    return d;
}

int main(){
    ifstream inputdata("The Shortest Path/inputdata.txt");
    ofstream outputdata("The Shortest Path/outputdata.txt");
	int T;
	inputdata>>T;
	for(int t=0; t<T; t++){
		int N, M, K, A, S;
		inputdata>>N>>M>>K>>A>>S;
		vector<FootPath> footPath;
		for(int i=0; i<M; i++){
			int u, v, w;
			inputdata>>u>>v>>w;
			footPath.push_back(FootPath(u-1, v-1, w));
		}
		vector<Road> road;
		for(int i=0; i<K; i++){
			int h, k;
			inputdata>>h>>k;
			vector<int> p(h);
			for(int j=0; j<h; j++){
				inputdata>>p[j];
				p[j]--;
			}
			vector<int> d(h);
			for(int j=0; j<h; j++)
				inputdata>>d[j];
			vector<int> t(k);
			for(int j=0; j<k; j++)
				inputdata>>t[j];
			road.push_back(Road(p, d, t));
		}
		vector<int> d=theShortestPath(footPath, road, N, A-1, S);
		copy(d.begin(), d.end(), ostream_iterator<int>(outputdata, " "));
		outputdata<<endl;
		copy(d.begin(), d.end(), ostream_iterator<int>(cout, " "));
		cout<<endl;
	}
    inputdata.close(), outputdata.close();
    return 0;
}