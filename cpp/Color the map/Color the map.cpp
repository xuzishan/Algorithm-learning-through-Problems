//
//  Color the map.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/13.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <hash_map>
#include <vector>
using namespace std;
struct Segment{
	pair<int, int> a, b;
	Segment(pair<int, int> a1, pair<int, int> b1):a(a1), b(b1){}
};
bool operator ==(pair<int, int> a, pair<int, int> b){
	return (a.first==b.first && a.second==b.second);
}
bool operator ==(Segment &s1, Segment &s2){
	return (s1.a==s2.a && s1.b==s2.b) || (s1.a==s2.b && s1.b==s2.a);
}
bool overlap(Segment &s1, Segment s2){
	if (s1==s2)
		return true;
	int v1=abs(s1.a.first-s1.b.first)*abs(s2.a.second-s2.b.second),
		v2=abs(s1.a.second-s1.b.second)*abs(s2.a.first-s2.b.first),
		v3=1,v4=2;
	if (v1==v2) {
		int x1=min(s1.a.first, s1.b.first), x2=max(s1.a.first, s1.b.first),
			y1=min(s1.a.second, s1.b.second), y2=max(s1.a.second, s1.b.second);
		if (s2.a != s1.a && s2.a != s1.b) {
			if (x1<=s2.a.first && s2.a.first<=x2){
				if (y1<=s2.a.second && s2.a.second<=y2) {
					v3=abs(s1.a.first-s2.a.first)*abs(s2.a.second-s1.b.second);
					v4=abs(s2.a.first-s1.b.first)*abs(s1.a.second-s2.a.second);
				}
		    }
		}else{
			if (x1<=s2.b.first && s2.b.first<=x2){
				if (y1<=s2.b.second && s2.b.second<=y2) {//s2.b在s1为对角线的矩形框内
					v3=abs(s1.a.first-s2.b.first)*abs(s2.b.second-s1.b.second);
					v4=abs(s2.b.first-s1.b.first)*abs(s1.a.second-s2.b.second);
                }
			}
		}
		if (v3==v4)
			return true;
		x1=min(s2.a.first, s2.b.first), x2=max(s2.a.first, s2.b.first);
		y1=min(s2.a.second, s2.b.second), y2=max(s2.a.second, s2.b.second);
		if (s1.a != s2.a && s1.a != s2.b) {
			if (x1<=s1.a.first && s1.a.first<=x2){
				if (y1<=s1.a.second && s1.a.second<=y2) {
					v3=abs(s2.a.first-s1.a.first)*abs(s1.a.second-s2.b.second);
					v4=abs(s1.a.first-s2.b.first)*abs(s2.a.second-s1.a.second);
				}
		    }
		}else{
			if (x1<=s1.b.first && s1.b.first<=x2){
				if (y1<=s1.b.second && s1.b.second<=y2) {//s2.b在s1为对角线的矩形框内
					v3=abs(s2.a.first-s1.b.first)*abs(s1.b.second-s2.b.second);
					v4=abs(s1.b.first-s2.b.first)*abs(s2.a.second-s1.b.second);
                }
			}
		}
		if (v3==v4)
			return true;
	}
	return false;
}
bool adjacent(vector<Segment> &a, vector<Segment> &b){
	int n=a.size(), m=b.size();
	for (int i=0; i<n; i++){
		Segment s1=a[i];
		for (int j=0; j<m; j++) {
			Segment s2=b[j];
			if (overlap(s1, s2))
				return true;
		}
	}
	return false;
}
class Map{
private:
	vector<vector<int>> G, solution;
	bool trivial;
	int n;
    void graphColor(int k, vector<int> &x){
        if (k>=n) {
			solution.push_back(vector<int>(x));
            return;
        }
        for (int color=1;color<=m; color++) {
            x[k]=color;
            int i=0;
            while (i<k) {
                if (G[i][k]==1 && x[i] == x[k])
                    break;
                i++;
            }
            if (i>=k)
				graphColor(k+1, x);
        }
    }
public:
	int m;
	Map(hash_map<string, vector<Segment>> map){
		n=map.size();
		vector<string> contry;
		for (hash_map<string, vector<Segment>>::iterator i=map.begin(); i!=map.end(); i++) {
			contry.push_back(i->first);
			G.push_back(vector<int>(n, 0));
		}
		trivial=true;
		for (int i=0; i<n; i++)
			for (int j=i+1; j<n; j++)
				if (adjacent(map[contry[i]], map[contry[j]])) {
					G[i][j]=1; G[j][i]=1;
					trivial=false;
				}
		m=1;
	}
	void colorTheMap(){
		if (trivial)
			return;
		int n=G.size();
		vector<int> x(n,0);
		m++;
		graphColor(0, x);
		while (solution.empty()) {
			m++;
			fill(x.begin(), x.end(), 0);
			graphColor(0, x);
		}
	}
};
int main(){
    ifstream inputdata("Color the map/inputdata.txt");
    ofstream outputdata("Color the map/outputdata.txt");
	string s;
	int n;
	inputdata>>n;getline(inputdata, s);
	while (n>0) {
		hash_map<string, vector<Segment>> map;
		for (int i=0; i<n; i++) {
			string contry;
			getline(inputdata, contry);
			int x, y;
			inputdata>>x>>y;getline(inputdata, s);
			pair<int, int> p0=make_pair(x, y), p1=make_pair(x, y);
			getline(inputdata, s);
			while (s!="-1") {
				istringstream strstr(s);
				strstr>>x>>y;
				pair<int, int> p2=make_pair(x, y);
				map[contry].push_back(Segment(p1, p2));
				p1=pair<int, int>(p2);
				getline(inputdata, s);
			}
			map[contry].push_back(Segment(p1, p0));
		}
		Map aMap=Map(map);
		aMap.colorTheMap();
		outputdata<<aMap.m<<endl;
		cout<<aMap.m<<endl;;
		inputdata>>n; getline(inputdata, s);
	}
    inputdata.close();
	outputdata.close();
	return 0;
} 