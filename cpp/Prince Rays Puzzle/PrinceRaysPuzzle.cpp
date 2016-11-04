//
//  PrinceRaysPuzzle.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/12/13.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
struct Tetrad{
    int x, y, z, number;
    Tetrad(int a, int b, int c, int d=0):x(a), y(b), z(c), number(d){}
};
bool operator==(const Tetrad& a, const Tetrad& b){
    return a.x==b.x && a.y==b.y && a.z==b.z;
}
vector<int> princeRayPuzzle(vector<string> a){
	list<Tetrad> BRICK;
	vector<int> result;
	int m=a.size();
	istringstream strstr; 
	for (int i=0; i<m; i++) {
		strstr=istringstream(a[i]);
		string cmd;
		strstr>>cmd;
		list<Tetrad>::iterator cell;
		if (cmd=="A" || cmd=="S") {
			int x, y, z, num;
			strstr>>x>>y>>z>>num;
			cell=find(BRICK.begin(), BRICK.end(), Tetrad(x, y, z));
			if (cell==BRICK.end())
				BRICK.push_back(Tetrad(x, y, z, cmd=="A"? num : -num));
			else
				cell->number=cell->number+(cmd=="A" ? num : -num);
		}else{
			int x1, y1, z1, x2, y2, z2, sum=0;
			strstr>>x1>>y1>>z1>>x2>>y2>>z2;
			for (cell=BRICK.begin(); cell!=BRICK.end(); cell++)
				if ((cell->x>=x1 && cell->y>=y1 && cell->z>=z1)&&(cell->x<=x2&&cell->y<=y2&&cell->z<=z2))
					sum+=cell->number;
			result.push_back(sum);
		}
	}
	return result;
}
int main(){
    ifstream inputdata("Prince Rays Puzzle/inputdata.txt");
    ofstream outputdata("Prince Rays Puzzle/outputdata.txt");
    int n;
    inputdata>>n;
	vector<string> a;
	string s;
	getline(inputdata, s);//断行
	getline(inputdata, s);
	while (s!="0") {
		a.push_back(s);
		getline(inputdata, s);
	}
    vector<int> result=princeRayPuzzle(a);
	copy(result.begin(), result.end(), ostream_iterator<int>(outputdata, "\n"));
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, "\n"));
    inputdata.close();
	outputdata.close();
    return 0;
}