//
//  Journey.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/17.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <iterator>
#include "../utility/Graph.h"
#include "../utility/priorityqueue.h"
struct edge{
    int end;
    int length;
    edge(int v, int n=0): end(v), length(n){}
};
bool operator==(const edge &a, const edge &b){
    return a.end==b.end;
}
struct Road{
	int u, v, w;
	Road(int a, int b, int c): u(a), v(b), w(c){}
};
struct Key{
	int index;
	int weight;
	Key(int x, int y):index(x), weight(y){}
};
bool operator<(const Key &a, const Key &b){
	return a.weight<b.weight;
}
bool operator>(const Key &a, const Key &b){
	return a.weight>b.weight;
}
bool operator==(const Key &a, const Key &b){
	return a.index==b.index;
}
class Byteland: public Graph<edge>{
public:
	Byteland(int n): Graph<edge>(n){}
    void insertEdge(int u, int v, int w=0) {
		list<edge>::iterator i=find(A[u].begin(), A[u].end(), edge(v));
        if (i==A[u].end())
			A[u].push_back(edge(v, w));
    }
	pair<vector<int>, vector<int>> dijkstra(int s){
		int n=scale;
		vector<int> d(n, INT_MAX);
		vector<int> pi(n, -1);
		vector<bool> poped(n, false);
		d[s]=0;
		PriorityQueue<Key, greater<Key>> Q;
		for (int i=0;i<n; i++) {
			Q.push(Key(i, d[i]));
		}
		while (!Q.empty()) {
			int u=Q.top().index; Q.pop();
			poped[u]=true;
			for (list<edge>::iterator i=A[u].begin(); i != A[u].end(); i++){
				int v=(*i).end, w=(*i).length;
				if (!poped[v])
					if (d[v] > d[u]+w){
						pi[v]=u;
						d[v]=d[u]+w;
						Key ele(v, d[v]);
						int i=Q.search(ele);
						ele.weight=d[v];
						Q.replace(ele, i);
					}
			}
		}
		return make_pair(pi, d);
	}
};

Byteland makeGraph(vector<Road> &road, int n){
	Byteland G(n);
	int m=road.size();
	for(int i=0; i<m; i++){
		int u=road[i].u, v=road[i].v, w=road[i].w;
		G.insertEdge(u, v, w);
		G.insertEdge(v, u, w);
	}
	return G;
}
int journey(vector<Road> &road, vector<int> &city, int n, int k){
	Byteland G=makeGraph(road, n);
	pair<vector<int>, vector<int>> p=G.dijkstra(k);
	vector<int> pi=p.first;
	vector<int> d=p.second;
	vector<Key> Q;
	vector<vector<int>> r;
	int m=city.size();
	for(int i=0; i<m; i++){
		Q.push_back(Key(i, d[city[i]]));
		r.push_back(vector<int>());
		int u=city[i];
		while(pi[u]!=-1){
			r[i].push_back(u);
			u=pi[u];
		}
		r[i].push_back(u);
	}
	sort(Q.begin(), Q.end());
	vector<bool> deleted(m, false);
	for(int i=0; i<m-1; i++)
		for(int j=i+1; j<m; j++){
			int u=*(r[Q[i].index].begin());
			if(find(r[Q[j].index].begin(), r[Q[j].index].end(), u)!=r[Q[j].index].end())
				deleted[Q[i].index]=true;
		}
	int i=0;
	while(deleted[Q[i].index])i++;
	int length=Q[i].weight;
	int j=i+1;
	while(j<m){
		vector<int>::iterator p=r[Q[i].index].end()-1, q=r[Q[j].index].end()-1;
		while(*p==*q){
			p--;
			q--;
		}
		p++, q++;
		length+=(Q[i].weight-d[*p]+Q[j].weight-d[*q]);
		i=j++;
	}
	return length;
}
int main(){
    ifstream inputdata("Journey/inputdata.txt");
    ofstream outputdata("Journey/outputdata.txt");
	int n, k;
	inputdata>>n>>k;
	while(n>0||k>0){
		vector<Road> road;
		int vn=0;
		for(int i=0; i<n-1; i++){
			int a, b, c;
			inputdata>>a>>b>>c;
			road.push_back(Road(a-1, b-1, c));
			vn=max(vn, max(a, b));
		}
		int j;
		inputdata>>j;
		vector<int> city;
		for(int i=0; i<j; i++){
			int mi;
			inputdata>>mi;
			city.push_back(mi-1);
		}
		int result=journey(road, city, vn, k-1);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>n>>k;
	}
    inputdata.close();
	outputdata.close();
	return 0;
} 