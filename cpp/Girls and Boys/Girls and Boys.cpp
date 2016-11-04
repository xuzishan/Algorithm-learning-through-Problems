//
//  Girls and Boys.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 15/6/15.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "../utility/Graph.h"
class Relation: public Graph<int>{
public:
	vector<bool> sex;
	vector<Color> color;
	Relation(int n):Graph(n){
		color=vector<Color>(n, WHITE);
		sex=vector<bool>(n, false);
	}
};
int bfsVisit(Relation &G, int s){
    queue<int> Q;
    int count=1, total=0;
    G.color[s]=GRAY;
    G.sex[s]=true;
    Q.push(s);
    while (!Q.empty()) {
        int u=Q.front(); Q.pop();
		list<int> Au=G.getList(u);
		for (list<int>::iterator i=Au.begin(); i != Au.end() ; i++) {
            int v=*i;
            if (G.color[v]==WHITE) {
                G.color[v]=GRAY;
                G.sex[v] = !G.sex[u];
                if (G.sex[v]) {
                    count++;
                }
                Q.push(v);
            }
        }
        G.color[u]=BLACK;
        total++;
    }
    return max(count, total-count);
}
int girlsAndBoys(Relation &G){
    int num=0;
    for (int s=0; s<G.size(); s++)
        if (G.color[s]==WHITE)
            num+=bfsVisit(G, s);
    return num;
}

int main(){
    ifstream inputdata("Girls and Boys/inputdata.txt");
    ofstream outputdata("Girls and Boys/outputdata.txt");
	int n;
	while(inputdata>>n){
		Relation G(n);
		for(int i=0; i<n; i++){
			int u, x;
			inputdata>>u;
			string s;
			inputdata>>s;inputdata>>s;
			x=atoi(s.substr(1,s.length()-2).c_str()); 
			for (int j=0; j<x; j++){
				int v;
				inputdata>>v;
				G.insertEdge(u, v);
			}
		}
		int result=girlsAndBoys(G);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
