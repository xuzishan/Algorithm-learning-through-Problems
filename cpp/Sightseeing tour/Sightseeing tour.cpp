//
//  Sightseeing tour.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Street{
	int x, y, d;
	Street(int a, int b, int c): x(a), y(b), d(c){}
};
string sightseeingTour(vector<Street> &street, int m){
    vector<int> indegree(m);
    vector<int> outdegree(m);
    vector<int> a(m);
	int n=street.size();
    for (int i=0; i<n; i++){
		int x=street[i].x, y=street[i].y, d=street[i].d;
        if (d==1) {
            outdegree[x-1]++;
            indegree[y-1]++;
        }else{
            a[x-1]++;
            a[y-1]++;
        }
    }
    for (int u=0; u<m; u++) {
        int ab=abs(indegree[u] - outdegree[u]);
        if  ((a[u]<ab)||((a[u]-ab)%2==1)) {
            return "impossible";
        }
    }
    return "possible";
}

int main(){
    ifstream inputdata("Sightseeing tour/inputdata.txt");
    ofstream outputdata("Sightseeing tour/outputdata.txt");
	int n;
	vector<vector<int>> solution;
	inputdata>>n;
	for(int i=0; i<n; i++){
		int m, s;
		inputdata>>m>>s;
		vector<Street> street;
		for(int k=0; k<s; k++){
			int x, y, d;
			inputdata>>x>>y>>d;
			street.push_back(Street(x, y, d));
		}
		string result=sightseeingTour(street,m);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
	inputdata.close();
	outputdata.close();
    return 0;
}