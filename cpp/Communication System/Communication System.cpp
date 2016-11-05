//
//  Communication System.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/9/16.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
struct Device{
	int b, p;
	Device(int x, int y):b(x), p(y){}
};
bool operator>(const Device &a, const Device &b){
	return a.b>b.b;
}
double communicationSystem(vector<vector<Device>> &devices, set<int> bands) {
    double r=0.0;
    int n=devices.size();
    for (int i=0; i<n; i++)
		sort(devices[i].begin(), devices[i].end(), greater<Device>());
	for (set<int>::iterator i=bands.begin(); i!=bands.end(); i++) {
        int B=*i, P=0, k;
        for (k=0; k<n; k++) {
            int temp=INT_MAX;
			for (int j=0; j<devices[k].size(); j++) {
                if (devices[k][j].b<B)
                    break;
                if (devices[k][j].p<temp)
                    temp=devices[k][j].p;
            }
            if (temp==INT_MAX)
                break;
            P+=temp;
        }
        if (k<n)
            continue;
        double r1=double(B)/double(P);
        if (r1 > r)
            r=r1;
    }
    return r;
}

int main(){
    ifstream inputdata("Communication System/inputdata.txt");
    ofstream outputdata("Communication System/outputdata.txt");
	int T;
	inputdata>>T;
	for(int t=0; t<T; t++){
		int N;
		inputdata>>N;
		vector<vector<Device>> devices(N, vector<Device>());
		set<int> bands;
		for(int i=0; i<N; i++){
			int mi;
			inputdata>>mi;
			for(int j=0; j<mi; j++){
				int b, p;
				inputdata>>b>>p;
				devices[i].push_back(Device(b, p));
				bands.insert(b);
			}
		}
		double result=communicationSystem(devices, bands);
		outputdata.precision(3);cout.precision(3);
		outputdata<<fixed<<result<<endl;
		cout<<fixed<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
    return 0;
}
