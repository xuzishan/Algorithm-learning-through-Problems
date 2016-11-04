//
//  CowSorting.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/2/4.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int cowSorting(vector<int> &a){
    int cost=0;
    int n=int(a.size());
    vector<int> b(a);
    sort(b.begin(), b.end());
    int a_min=b[0];
    while (n > 0) {
        int j=0;
        while (a[j]==0)
            j++;
        int ti=INT_MAX, sum=a[j];
        int k=1, ai=a[j];
        a[j]=0; n--;
        while (b[j]!=ai) {
            k++;
            if (ti>b[j])
                ti=b[j];
            sum+=b[j];
            j=int(distance(a.begin(), find(a.begin(), a.end(), b[j])));
            a[j]=0; n--;
        }
        if (k>1) {
            int mi = min((k-2)*ti, ti+(k+1)*a_min);
            cost+=(sum+mi);
        }
    }
    return cost;
}
int main(){
    ifstream inputdata("Cow Sorting/inputdata.txt");
    ofstream outputdata("Cow Sorting/outputdata.txt");
    int n;
    inputdata>>n;
    while (n){
        vector<int> a(n);
        for(int i=0; i<n; i++)
            inputdata>>a[i];
        int result=cowSorting(a);
        outputdata<<result<<endl;
        cout<<result<<endl;
        inputdata>>n;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}