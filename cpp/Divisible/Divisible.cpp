//
//  Divisible.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include <algorithm>
using namespace std;
vector<int> preprocess(vector<int> &a, int K){
	set<int> S;
    for (int i=0;  i<a.size(); i++) {
        a[i]=a[i]%K;
        if(a[i]!=0){
            if(S.find(a[i])!=S.end()){
                S.erase(a[i]);
                continue;
            }
            bool insert=true;
            for (set<int>::iterator it=S.begin(); it!=S.end(); it++) {
                if((*it-a[i])%K==0||(*it+a[i])%K==0){
                    S.erase(it);
                    insert=false;
                    break;
                }
            }
            if(insert)
                S.insert(a[i]);
        }
	}
    vector<int> b;
	for (set<int>::iterator x=S.begin(); x!=S.end(); x++) {
        b.push_back(*x);
    }
    return b;
}
bool divisable(vector<int> &a, int K) {
    vector<int> b=preprocess(a, K);
	int n=b.size();
    if(n==0)
        return true;
    if (n<2) {
        return false;
    }
    int p=1;
    for (int i=0; i<n-1; i++) {
        p*=2;
    }
    for (int i=0; i<p; i++) {
		bitset<32> op(i);
        int sum=b[0];
        for (int j=1; j<n; j++) {
            if (op[j-1]==0) {
                sum+=b[j];
            }else{
                sum-=b[j];
            }
        }
        if (sum%K==0) {
            return true;
        }
    }
    return false;
}

int main(){
    ifstream inputdata("Divisible/inputdata.txt");
    ofstream outputdata("Divisible/outputdata.txt");
	int N;
	inputdata>>N;
	while (N>0) {
		int K;
		inputdata>>K;
		vector<int> a(N);
		for (int i=0; i<N; i++)
			inputdata>>a[i];
		bool result=divisable(a, K);
		if(result){
			outputdata<<"Divisable"<<endl;
			cout<<"Divisable"<<endl;
		}else{
			outputdata<<"Not divisable"<<endl;
			cout<<"Not divisable"<<endl;
		}
		inputdata>>N;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}