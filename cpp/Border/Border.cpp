//
//  Border.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;
vector<string> border(string path, int x, int y){
	vector<string> bitmap(32, "................................");
	int i=0;
	while (path[i] != '.') {
		switch( path[i]) {
			case 'E':
				bitmap[32-y][x++]='X';
				break;
			case 'W':
				bitmap[31-y][--x]='X';
				break;
			case 'N':
				bitmap[32-(++y)][x]='X';
				break;
			case 'S':
				bitmap[32-(y--)][x-1]='X';
				break;
			defalut: break;
		}
		i++;
	}
	return bitmap;
}
int main(){
    ifstream inputdata("Border/inputdata.txt");
    ofstream outputdata("Border/outputdata.txt");
	int T;
	inputdata>>T;
	for (int t=0; t<T; t++){
		int x, y;
		inputdata>>x>>y;
		string path;
		getline(inputdata, path);//断行
		getline(inputdata, path);
		vector<string> bitmap=border(path, x, y);
		copy(bitmap.begin(), bitmap.end(), ostream_iterator<string>(outputdata, "\n")); 
		copy(bitmap.begin(), bitmap.end(), ostream_iterator<string>(cout, "\n")); 
	}
    inputdata.close();
    outputdata.close();
    return 0;
}