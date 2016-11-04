//
//  Jills Tour Paths.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/17.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
class Map {
	vector<vector<int>> &g;
	int sv, dv, maxdist, length;
	vector<int> path;
public:
	vector<vector<int>> solution;
	Map(vector<vector<int>> &G, int SV, int DV, int MAXDIST): g(G), sv(SV-1), dv(DV-1), maxdist(MAXDIST){
		path.push_back(sv);
		length=0;
		solution=vector<vector<int>>();
	}
	void jillsTourPaths(int k){
		if (path[k-1]==dv) {
			solution.push_back(vector<int>(path));
			solution[solution.size()-1].insert(solution[solution.size()-1].begin(), length);
			return;
		}
		int nv=g.size();
		for (int v=0; v<nv; v++)
			if (g[path[k-1]][v]>0 && find(path.begin(), path.end(), v)==path.end())
				if (length+g[path[k-1]][v]<=maxdist) {
					path.push_back(v);
					length+=g[path[k-1]][v];
					jillsTourPaths(k+1);
					length-=g[path[k-1]][v];
					path.pop_back();
				}
	}
	void fix(){
		int n=solution.size();
		for(int i=0; i<n; i++){
			int m=solution[i].size();
			for (int j=1; j<m; j++)
				solution[i][j]++;
		}
		sort(solution.begin(), solution.end(),less<vector<int>>());
	}
};
int main(){
    ifstream inputdata("Jill's Tour Paths/inputdata.txt");
    ofstream outputdata("Jill's Tour Paths/outputdata.txt");
	int NV, number=0;
	inputdata>>NV;
	while (NV>0) {
		number++;
		vector<vector<int>> G(NV, vector<int>(NV, 0));
		int NR;
		inputdata>>NR;
		for (int i=0; i<NR; i++) {
			int C1, C2, DIST;
			inputdata>>C1>>C2>>DIST;
			G[C1-1][C2-1]=DIST;
			G[C2-1][C1-1]=DIST;
		}
		int SV, DV, MAXDIST;
		inputdata>>SV>>DV>>MAXDIST;
		Map aMap(G, SV, DV, MAXDIST);
		aMap.jillsTourPaths(1);
		aMap.fix();
		outputdata<<"Case "<<number<<":\n";
		cout<<"Case "<<number<<":\n";
		for (int i=0; i<aMap.solution.size(); i++) {
			outputdata<<aMap.solution[i][0]<<": ";
			copy(aMap.solution[i].begin()+1, aMap.solution[i].end(), ostream_iterator<int>(outputdata, " "));
			outputdata<<endl;
			cout<<aMap.solution[i][0]<<": ";
			copy(aMap.solution[i].begin()+1, aMap.solution[i].end(), ostream_iterator<int>(cout, " "));
			cout<<endl;
		}
		outputdata<<endl;
		cout<<endl;
		inputdata>>NV;
	}
    inputdata.close();
	outputdata.close();
	return 0;
} 