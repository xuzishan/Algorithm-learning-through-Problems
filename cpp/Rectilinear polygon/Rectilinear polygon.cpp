//
//  Rectilinear polygon.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/10/13.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int searchx(vector<pair<int, int>> &a, pair<int, int> b){
	int min=INT_MAX, j=-1, n=a.size(), i;
	for (i=0; i<n; i++) {
		if (a[i].first==b.first){
			int x=abs(a[i].second-b.second);
			if (x<min){
				j=i;
				min=x;
			}
		}
	}
	return j;
}
int searchy(vector<pair<int, int>> &a, pair<int, int> b){
	int min=INT_MAX, j=-1, n=a.size(), i;
	for (i=0; i<n; i++) {
		if (a[i].second==b.second){
			int x=abs(a[i].first-b.first);
			if (x<min){
				j=i;
				min=x;
			}
		}
	}
	return j;
}
bool crossv(vector<pair<pair<int, int>, int>> &a, pair<pair<int, int>, int> b){
	int y1=b.first.first, y2=b.first.second, x=b.second;
	for (vector<pair<pair<int, int>, int>>::iterator p=a.begin(); p!=a.end(); p++){
		int x1=p->first.first, x2=p->first.second, y=p->second;
        if (x1<x && x<x2 && y1<y && y<y2)
            return true;
	}
	return false;
}
bool crossh(vector<pair<pair<int, int>, int>> &a, pair<pair<int, int>, int> b){
	int x1=b.first.first, x2=b.first.second, y=b.second;
	for (vector<pair<pair<int, int>, int>>::iterator p=a.begin(); p!=a.end(); p++){
		int y1=p->first.first, y2=p->first.second, x=p->second;
        if (x1<x && x<x2 && y1<y && y<y2)
            return true;
	}
	return false;
}
int rectilinearPolygon(vector<pair<int, int>> p){
	int length=0;
	pair<int, int> start=p[0], current=start;
	p.erase(p.begin());
	vector<pair<pair<int, int>, int>> horizontal, vertical;
	while (p.size()>0) {
		int i=searchx(p, current);
		if (i>-1) {
			int y1=min(p[i].second, current.second), y2=p[i].second+current.second-y1;
			pair<pair<int, int>, int> segment_v(pair<int, int>(y1, y2), current.first);
			if (crossv(horizontal, segment_v))
				return -1;
			vertical.push_back(segment_v);
			length+=abs(current.second-p[i].second);
			current=p[i];
			p.erase(p.begin()+i);
		}else{
			i=searchy(p, current);
			if (i>-1) {
				int x1=min(p[i].first, current.first), x2=p[i].first+current.first-x1;
				pair<pair<int, int>, int> segment_h(pair<int, int>(x1, x2), current.second);
				if (crossh(vertical, segment_h))
					return -1;
				horizontal.push_back(segment_h);
				length+=abs(current.first-p[i].first);
				current=p[i];
				p.erase(p.begin()+i);
			}else
				return -1;
		}
	}
	if (current.first==start.first) {
		int y1=min(start.second, current.second), y2=current.second+start.second-y1;
		pair<pair<int, int>, int> segment_v(pair<int, int>(y1, y2), current.first);
		if (crossv(horizontal, segment_v))
			return -1;
		length+=abs(current.second-start.second);
	}else if (current.second==start.second) {
		int x1=min(start.first, current.first), x2=current.first+start.first-x1;
		pair<pair<int, int>, int> segment_h(pair<int, int>(x1, x2), current.second);
		if (crossv(vertical, segment_h))
			return -1;
		length+=abs(current.first-start.first);
	}else
		return -1;
	return length;
}
int main(){
	ifstream inputdata("Rectilinear polygon/inputdata.txt");
	ofstream outputdata("Rectilinear polygon/outputdata.txt");
	int T;
	inputdata>>T;
	for (int t=0; t<T; t++) {
		int n;
		vector<pair<int, int>> p;
		inputdata>>n;
		for (int i=0; i<n; i++) {
			int x, y;
			inputdata>>x>>y;
			p.push_back(pair<int, int>(x, y));
		}
		int result=rectilinearPolygon(p);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
	inputdata.close();
	outputdata.close();
	return 0;
}