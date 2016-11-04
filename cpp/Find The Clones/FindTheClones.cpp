//
//  FindTheClones.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/12/13.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <hash_map>
using namespace std;
vector<int> findTheClones(const vector<string> &a){
	int n=a.size();
    hash_map<string,int> DNAS;
    for (int i=0; i<n; i++) {
        DNAS[a[i]]++;
    }
    vector<int> solution=vector<int>(n, 0);
    hash_map<string,int>::iterator dna;
    for (dna=DNAS.begin(); dna!=DNAS.end(); dna++)
        solution[dna->second-1]++;
	return solution;
}
int main(){
    ifstream inputdata("Find The Clones/inputdata.txt");
    ofstream outputdata("Find The Clones/outputdata.txt");
    int n, m;
    inputdata>>n>>m;
    while (n!=0 || m!=0) {
		vector<string> a;
		for(int i=0; i<n; i++){
			string sample;
			inputdata>>sample;
			a.push_back(sample);
		}
		vector<int> solution=findTheClones(a);
		copy(solution.begin(), solution.end(), ostream_iterator<int>(outputdata, "\n"));
		copy(solution.begin(), solution.end(), ostream_iterator<int>(cout, "\n"));
        inputdata>>n>>m;
    }
    inputdata.close();outputdata.close();
    return 0;
}