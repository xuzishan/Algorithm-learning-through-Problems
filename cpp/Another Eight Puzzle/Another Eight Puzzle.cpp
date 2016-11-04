//
//  Another Eight Puzzle.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/18.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <bitset>
//#include <algorithm>
using namespace std;
class Puzzle {
	vector<bitset<8>> A;
	vector<int> index;
	vector<int> x;
	vector<vector<int>> solution;
public:
	Puzzle(vector<int> &a){
		A=vector<bitset<8>>();
		A.push_back(bitset<8>("00001110"));
		A.push_back(bitset<8>("00110101"));
		A.push_back(bitset<8>("01111011"));
		A.push_back(bitset<8>("01100101"));
		A.push_back(bitset<8>("10100110"));
		A.push_back(bitset<8>("11011110"));
		A.push_back(bitset<8>("10101100"));
		A.push_back(bitset<8>("01110000"));
		vector<int> b;
		for (int i=0; i<8; i++)
			b.push_back(i+1);
		x=vector<int>(a);
		for (int i=0; i<8; i++) {
			if (a[i]!=0){
				vector<int>::iterator p=find(b.begin(), b.end(), a[i]);
				b.erase(p);
			}else
				index.push_back(i);
		}
		x=vector<int>(a);
		for (int i=0; i<index.size(); i++)
			x[index[i]]=b[i];
	}
private:
	bool isPartial(int k) {
		int j=0;
        for (j=0; j<k; j++)
			if (A[j][k] && abs(x[j]-x[k])==1)
				break;
		if (j==k)
			return true;
        return false;
	}
public:
    void permutation(int k){
        if (k>=8) {
            solution.push_back(vector<int>(x));
            return;
        }
		vector<int>::iterator k1=find(index.begin(), index.end(),k);
        if (k1!=index.end()) {
			for (int i=distance(index.begin(), k1); i!=index.size(); i++) {
				if (index[i] != k)
					swap(x[index[i]], x[k]);
                if (isPartial(k))
                    permutation(k+1);
                if (index[i] != k)
                    swap(x[index[i]], x[k]);
			}
        }else
            if (isPartial(k))
				permutation(k+1);
	}
	string toString(){
		string s;
		int n=solution.size();
		switch (n) {
			case 0: s="No answer\n";break;
			case 2: s="Not unique\n"; break;
			default: s="                ";
				for (int i=0; i<8; i++)
					s[2*i]='0'+solution[0][i];
				s[15]='\n';
		}
		return s;
	}
};
string anotherEightPuzzle(vector<int> &a){
	Puzzle p(a);
	p.permutation(0);
	return p.toString();
}
int main(){
    ifstream inputdata("Another Eight Puzzle/inputdata.txt");
    ofstream outputdata("Another Eight Puzzle/outputdata.txt");
	int T;
	inputdata>>T;
	for (int t=1; t<=T; t++){
		vector<int> a(8);
		for (int i=0; i<8; i++)
			inputdata>>a[i];
		string result=anotherEightPuzzle(a);
		outputdata<<"Case "<<t<<": "<<result;
		cout<<"Case "<<t<<": "<<result;
	}
    inputdata.close();
    outputdata.close();
  return 0;
}