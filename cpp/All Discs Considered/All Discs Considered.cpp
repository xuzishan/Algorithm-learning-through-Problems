//
//  All Discs Considered.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/2/27.
//  Copyright (c) 2016Äê xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <algorithm>
#include "../utility/Graph.h"
class Software:public Graph<int>{
public:
    vector<Color> color;
    stack<int> toplogicalSequance;
    bool acyclic;
    Software(int n):Graph<int>(n) {
        color=vector<Color>(n, WHITE);
        toplogicalSequance=stack<int>();
        acyclic=false;
    }
	int getScale(){return scale;}
	void dfsVisit(int u);
	friend void toplogicalSort(Software* G);
};
void Software::dfsVisit(int u){
    color[u]=GRAY;
	for (list<int>::iterator i=A[u].begin(); i != A[u].end(); i++) {
        int v=*i;
        if (color[v] == WHITE)
            dfsVisit(v);
        else if (color[v]==GRAY) {
            acyclic=true;
            return;
        }
    }
    color[u]=BLACK;
    toplogicalSequance.push(u);
}
void toplogicalSort(Software &G){
	for (int s=0; s<G.getScale(); s++) {
        if (G.color[s]==WHITE) {
            G.dfsVisit(s);
            if (G.acyclic)
				return;
        }
    }
}
Software makeGraph(vector<pair<int, int>> &dependence, int N1, int N2) {
    Software G(N1+N2);
	int n=dependence.size();
    for (int i=0; i<n; i++){
		int u=dependence[i].first, v=dependence[i].second;
        G.insertEdge(u, v);
    }
    return G;
}
bool isOneDisk(int a, int b, int n) {
    return (a<n && b<n) || (a>=n && b>=n);
}
int allDiscsConsidered(vector<pair<int, int>> &dependence, int N1, int N2){
    Software G=makeGraph(dependence, N1, N2);
    toplogicalSort(G);
    vector<int> p;
    if (!G.acyclic) {
        while (!G.toplogicalSequance.empty()){
            p.push_back(G.toplogicalSequance.top());
            G.toplogicalSequance.pop();
        }
    }
    int num=2;
    for (int k=0; k<N1+N2; k++)
        if (k<N1+N2-1 && !isOneDisk(p[k], p[k+1], N1))
            if (k>1 && !isOneDisk(p[k-1], p[k], N1)){
				if (find(dependence.begin(), dependence.end(), make_pair(p[k+1], p[k])) == dependence.end())
                    swap(p[k], p[k+1]);
			}else
                num++;
    return num;
}
int main(){
    ifstream inputdata("All Discs Considered/inputdata.txt");
    ofstream outputdata("All Discs Considered/outputdata.txt");
	int n1, n2, d;
	inputdata>>n1>>n2>>d;
	while(n1>0||n2>0||d>0){
		vector<pair<int, int>> dependence;
		for(int i=0; i<d; i++){
			int x, y;
			inputdata>>x>>y;
			dependence.push_back(make_pair(y-1, x-1));
		}
		int result=allDiscsConsidered(dependence, n1, n2);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>n1>>n2>>d;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
