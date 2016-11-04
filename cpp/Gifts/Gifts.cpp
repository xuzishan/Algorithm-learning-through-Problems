//
//  Gifts.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/10/24.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Gift{
	int value, index;
	Gift(int v, int i):value(v), index(i){}
};
bool operator>(const Gift &a, const Gift &b){
	return a.value>b.value;
}
int gifts(vector<int> &X, vector<int> &Y, int k1, int A1, int B1, int k2, int A2, int B2){
    int sum=0;
	int n=X.size();
    vector<Gift> S1, S2;
    for (int i=0; i<n; i++) {
        int v1=A1*X[i]+B1*Y[i], v2=A2*X[i]+B2*Y[i];
		v1>v2?S1.push_back(Gift(v1,i)):S2.push_back(Gift(v2, i));
    }
	int n1=S1.size(), n2=S2.size();
    if (n1>k1) {
		sort(S1.begin(), S1.end(), greater<Gift>());
        for (int i=0; i<n1-k1; i++){
            S2.push_back(Gift(A2*X[S1[k1+i].index]+B2*Y[S1[k1+i].index], 0));
			n2++;
		}
		S1.erase(S1.begin()+k1, S1.end());
		n1-=k1;
    }else if (n2>k2) {
		sort(S2.begin(), S2.end(), greater<Gift>());
        for (int i=0; i<n2-k2; i++){
            S1.push_back(Gift(A1*X[S2[k2+i].index]+B1*Y[S2[k2+i].index], 0));
			n1++;
		}
		S2.erase(S2.begin()+k2, S1.end());
		n2-=k2;
    }
    for (int i=0; i<n1; i++)
		sum+=S1[i].value;
    for (int i=0; i<n2; i++)
        sum+=S2[i].value;
    return sum;
}
int main(){
    ifstream inputdata("Gifts/inputdata.txt");
    ofstream outputdata("Gifts/outputdata.txt");
	int n;
	inputdata>>n;
	vector<int> X, Y;
	for(int i=0; i<n; i++){
		int x, y;
		inputdata>>x>>y;
		X.push_back(x);
		Y.push_back(y);
	}
	int A1, B1, k1, A2, B2, k2;
	inputdata>>k1>>A1>>B1;
	inputdata>>k2>>A2>>B2;
	int result=gifts(X, Y, k1, A1, B1,k2, A2, B2);
	outputdata<<result<<endl;
	cout<<result<<endl;
    inputdata.close();
	outputdata.close();
    return 0;
}
