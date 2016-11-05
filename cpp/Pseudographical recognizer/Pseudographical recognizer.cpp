//
//  Pseudographical recognizer.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/3/2.
//  Copyright (c) 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
bool horizontal(vector<string> &picture, int m){
	int n=picture.size();
	int max=0;
	for (int i=0; i<n; i++){
		int j=picture[i].find('-');
		if(j>-1){
			int k=j;
			while(k<m&&picture[i][k]=='-')k++;
			if (k-j>max)
				max=k-j;
		}
	}
	if (max>1||max==m)
		return true;
	return false;
}
bool vertical(vector<string> &picture, int m){
	int n=picture.size();
	int max=0;
	for (int i=0; i<n; i++){
		int j=picture[i].find('|');
		if (j>-1) {
			int k=i;
			while(k<n && picture[k][j]=='|')k++;
			if (k-i>max)
				max=k-i;
		}
	}
	if(max>1||max==n)
		return true;
	return false;
}
bool slashLeft(vector<string> &picture, int m){
	int n=picture.size();
	int max=0;
	for (int i=0; i<n; i++){
		int j=picture[i].find('/');
		if(j>-1){
			int k=i, h=j;
			while(k<n&&h>-1&&picture[k][h]=='/'){
				k++;
				h--;
			}
			if(k-i>max)
				max=k-i;
		}
	}
	if(max>1||max==n||max==m)
		return true;
	return false;
}
bool slashRight(vector<string> &picture, int m){
	int n=picture.size();
	int max=0;
	for (int i=0; i<n; i++){
		int j=picture[i].find('\\');
		if(j>-1){
			int k=i, h=j;
			while(k<n&&h<m&&picture[k][h]=='\\'){
				k++;
				h++;
			}
			if(k-i>max)
				max=k-i;
		}
	}
	if(max>1||max==n||max==m)
		return true;
	return false;
}
string pseudographicalRecognizer(vector<string> &picture, int m){
	bool r=horizontal(picture, m)||vertical(picture, m)||slashLeft(picture, m)||slashRight(picture, m);
	if (r)
		return "CORRECT";
	return "INCORRECT";
}
int main(){
    ifstream inputdata("Pseudographical recognizer/inputdata.txt");
    ofstream outputdata("Pseudographical recognizer/outputdata.txt");
	int T;
	inputdata>>T;
	for(int t=0; t<T; t++){
		int N, M;
		inputdata>>N>>M;
		vector<string> picture(N);
		for (int i=0; i<N; i++)
			inputdata>>picture[i];
		string result=pseudographicalRecognizer(picture,M);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}