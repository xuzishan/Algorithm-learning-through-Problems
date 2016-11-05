//
//  The Best Farm.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/4.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
int theBestFarm(vector<pair<int, int>> &cells, vector<int> &values) {
	int n=cells.size();
	int max=INT_MIN;
	vector<bool> visited(n, false);
	for (int i=0; i<n; i++) {
		if (!visited[i]) {
			int value=0;
			visited[i]=true;
			queue<int> Q;
			Q.push(i);
			while (!Q.empty()) {
				int k=Q.front(); Q.pop();
				value+=values[k];
				int x=cells[k].first, y=cells[k].second;
				vector<pair<int, int>>::iterator p;
				p=find(cells.begin(), cells.end(), pair<int, int>(x-1, y));
				if (p!=cells.end()){
					int j=distance(cells.begin(), p);
					if (!visited[j]) {
						Q.push(j);
						visited[j]=true;
					}
				}
				p=find(cells.begin(), cells.end(), pair<int, int>(x+1, y));
				if (p!=cells.end()){
					int j=distance(cells.begin(), p);
					if (!visited[j]) {
						Q.push(j);
						visited[j]=true;
					}
				}
				p=find(cells.begin(), cells.end(), pair<int, int>(x, y-1));
				if (p!=cells.end()){
					int j=distance(cells.begin(), p);
					if (!visited[j]) {
						Q.push(j);
						visited[j]=true;
					}
				}
				p=find(cells.begin(), cells.end(), pair<int, int>(x, y+1));
				if (p!=cells.end()){
					int j=distance(cells.begin(), p);
					if (!visited[j]) {
						Q.push(j);
						visited[j]=true;
					}
				}
			}
			if (max<value)
				max=value;
		}
	}
	return max;
}
int main(){
    ifstream inputdata("The Best Farm/inputdata.txt");
    ofstream outputdata("The Best Farm/outputdata.txt");
	int N;
	inputdata>>N;
	while (N>0) {
		vector<pair<int, int>> cells;
		vector <int> values;
		for (int i=0; i<N; i++){
			int x, y, v;
			inputdata>>x>>y>>v;
			cells.push_back(pair<int, int>(x, y));
			values.push_back(v);
		}
		int result=theBestFarm(cells, values);
		outputdata<<result<<endl;
		cout<<result<<endl;
		inputdata>>N;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}