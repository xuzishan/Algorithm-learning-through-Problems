//
//  DNA Sorting.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/10/27.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
int inversion(const string &dna) {
	int count=0, n=dna.length();
    int cC=0, cG=0, cT=0;
    for (int i=0; i<n; i++)
        switch (dna[i]) {
            case 'A': count+=(cC+cG+cT);
				break;
            case 'C': count+=(cG+cT);
				cC++;
				break;
            case 'G': count+=cT;
				cG++;
				break;
            default: cT++;
        }
    return count;
}
struct Dna: public string{
	int inv;
	Dna(string s="", int i=0):string(s),inv(i){}
};
bool operator<(const Dna &a, const Dna &b){
	return a.inv<b.inv;
}
void dnaSorting(vector<Dna> &dnas){
	int m=dnas.size();
    for (int i=0; i<m; i++)
		dnas[i].inv=inversion(dnas[i]);
	sort(dnas.begin(), dnas.end());
}
int main(){
    ifstream inputdata("DNA Sorting/inputdata.txt");
    ofstream outputdata("DNA Sorting/outputdata.txt");
	int n, m;
	inputdata>>n>>m;
	vector<Dna> dnas;
	for (int i=0; i<m; i++){
		Dna s;
		inputdata>>s;
		dnas.push_back(s);
	}
	dnaSorting(dnas);
	copy(dnas.begin(), dnas.end(), ostream_iterator<string>(outputdata,"\n"));
	copy(dnas.begin(), dnas.end(), ostream_iterator<string>(cout,"\n"));
    inputdata.close();
    outputdata.close();
    return 0;
}