//
//  partygame.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/11/22.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
bool partyGame(vector<int> a){
    int n=int(a.size());
    int count=0;
    for (int i=0; i<n; i++)
        if (a[i]%2)
            count++;
    return (count%2)==0;
}
int main(){
    ifstream inputdata("Party Game/inputdata.txt");
    ofstream outputdata("Party Game/outputdata.txt");
    int n;
    inputdata>>n;
    while (n) {
        vector<int> a(n);
        a[n-1]=n-1;
        for (int i=0; i<n-1; i++)
            inputdata>>a[i];
        if (partyGame(a)){
            outputdata<<"Maybe truth"<<endl;
            cout<<"Maybe truth"<<endl;
        }else{
            outputdata<<"Lie absolutely"<<endl;
            cout<<"Lie absolutely"<<endl;
        }
        inputdata>>n;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}