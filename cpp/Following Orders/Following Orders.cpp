//
//  Following Orders.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/2/27.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
using namespace std;
class Order{
    string x;
    vector<list<char>> omg;
    int n;
    void backtrackier(int k){
        if (k>=n) {
            orders.push_back(string(x));
            return;
        }
		for (list<char>::iterator i=omg[k].begin(); i != omg[k].end(); i++) {
            char varable=(*i);
            int j;
            for (j=0; j<k; j++) {
                if (x[j]==varable) {
                    break;
                }
            }
            if (j>=k) {
                x[j]=varable;
                backtrackier(k+1);
            }
        }
    }
public:
    vector<string> orders; 
    Order(string &v, vector<pair<int, int>> &r){
        orders=vector<string>();
        x="";
		n=v.length();
        omg=vector<list<char>>(n, list<char>());
        vector<pair<int, int>> constraints;
        vector<int> befor(n, 0);
        vector<int> after(n, 0);
		for (int i=0; i<r.size(); i++){
			int x=r[i].first, y=r[i].second;
            after[x]++; befor[y]++;
            for (int j=0; j<constraints.size(); j++){
				int u=constraints[j].first, v=constraints[j].second;
                if (v==x) {
                    befor[y]++;
                    after[u]++;
                }
                if (y==u) {
                    befor[v]++;
                    after[x]++;
                }
            }
            constraints.push_back(make_pair(x, y));//(x, y)作为一条有向边
        }
        for (int i=0; i<n; i++) {
            for (int j=befor[i]; j<n-after[i]; j++)
                omg[j].push_back(v[i]);
            x+=" ";
        }
    }
    void followingOrders(){
        backtrackier(0);
    }
};
int main(){
    ifstream inputdata("Following Orders/inputdata.txt");
    ofstream outputdata("Following Orders/outputdata.txt");
	string line;
	while(getline(inputdata,line)){
		istringstream s(line);
		string varables;
		char c;
		while(s>>c)
			varables+=c;
		getline(inputdata, line);
		s=istringstream(line);
		char x, y;
		vector<pair<int, int>> edges;
		while(s>>x){
			s>>y;
			int u=varables.find(x), v=varables.find(y);
			edges.push_back(make_pair(u, v));
		}
		Order r(varables, edges);
		r.followingOrders();
		for(int i=0; i<r.orders.size(); i++){
			outputdata<<r.orders[i]<<endl;
			cout<<r.orders[i]<<endl;
		}
		outputdata<<endl;
		cout<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
