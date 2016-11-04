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
#include <iterator>
#include "../utility/Graph.h"
struct edge{
    int end;
    int num;
    edge(int v, int n=0): end(v), num(n){}
};
bool operator==(const edge &a, const edge &b){
    return a.end==b.end;
}
class City: public Graph<edge>{
public:
    City(int n): Graph(n) {}
    void insertEdge(int u, int v, int n) {
        if (A[u].empty()) {
            A[u].push_back(edge(v, n));
        }else{
			list<edge>::iterator p=A[u].begin();
            while (p != A[u].end() && (*p).num<n) {
                p++;
            }
            A[u].insert(p, edge(v, n));
        }
    }
};
struct Street{
	int x, y, z;
	Street(int a, int b, int c):x(a), y(b), z(c){}
};
void tour(City &g, stack<int> &s, stack<int> &path, int u){
    int v=u;
    while (true) {
		list<edge> lt=g.getList(v);
        if (lt.empty()) {
            break;
        }
		int w=(lt).begin()->end;
        s.push(v);
		path.push(lt.begin()->num);
        g.deleteEdge(v, edge(w));
        g.deleteEdge(w, edge(v));
        v=w;
    }
}
list<int> eulerPath(City &G, int start){
    list<int> l;
	int n=G.getScale();
	for (int i=0; i<n; i++) {
		int m=G.getList(i).size();
		if (m%2 == 1) {
            return l;
        }
    }
    City g(G);
    stack<int> path;
    stack<int> s;
    tour(g, s, path, start);
    while (!s.empty()){
        int x=s.top(); s.pop();
        l.push_front(path.top()); path.pop();
        tour(g, s, path, x);
    }
    return l;
}
pair<City, int> makeGraph(vector<Street> &street) {
    int m=INT_MAX, n=INT_MIN, start=0;
    for (int i=0; i<street.size(); i++){
		int x=street[i].x, y=street[i].y, z=street[i].z;
		if (n<max(x, y)) {
            n=max(x, y);
        }
        if (m>z) {
            m=z;
            start=x;
        }
    }
    City G(n+1);
    for (int i=0; i<street.size(); i++){
		int x=street[i].x, y=street[i].y, z=street[i].z;
        G.insertEdge(x, y, z);
        G.insertEdge(y, x, z);
    }
    return make_pair(G, start);
}
list<int> johnsTrip(vector<Street> &street){
    pair<City, int> p=makeGraph(street);
	City G=p.first;
	int start=p.second;
    list<int> path=eulerPath(G, start);
    return path;
}
int main(){
    ifstream inputdata("John's trip/inputdata.txt");
    ofstream outputdata("John's trip/outputdata.txt");
	int x, y;
	inputdata>>x>>y;
	while(x>0||y>0){
		vector<Street> street;
		while(x>0||y>0){
			int z;
			inputdata>>z;
			street.push_back(Street(x-1, y-1, z));
			inputdata>>x>>y;
		}
		list<int> result=johnsTrip(street);
		if (!result.empty()){
			copy(result.begin(), result.end(), ostream_iterator<int>(outputdata, " "));
			outputdata<<endl;
			copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
			cout<<endl;
		}else{
			outputdata<<"Round trip does not exist."<<endl;
			cout<<"Round trip does not exist."<<endl;
		}
		inputdata>>x>>y;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
