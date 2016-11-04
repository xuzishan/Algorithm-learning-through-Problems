//
//  crossingriver.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/11/24.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int crossingRiver(vector<int>& a){
    int n=a.size();
    int t=0;
    while (n>=4) {
        int x=2*a[0]+a[n-2]+a[n-1], y=a[0]+2*a[1]+a[n-1];
        t+=min(x, y);
        n-=2;
    }
    if (n==3)
        t+=(a[0]+a[1]+a[2]);
    else if (n>0)
        t+=a[n-1];
    return t;
}
int main(){
    ifstream inputdata("Crossing River/inputdata.txt");
    ofstream outputdata("Crossing River/outputdata.txt");
    int t;
    inputdata>>t;
    for(int i=0; i<t; i++){
        int n;
        inputdata>>n;
        vector<int> a(n);
        for(int j=0; j<n; j++)
            inputdata>>a[j];
		sort(a.begin(), a.end());
        int time=crossingRiver(a);
        outputdata<<time<<endl;
        cout<<time<<endl;
    }
    inputdata.close(), outputdata.close();
    return 0;
}