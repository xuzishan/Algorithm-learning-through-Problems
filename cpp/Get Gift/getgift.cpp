//
//  gift.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/11/19.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;
int getGift(int x, int a, int b){
    int m=1;
    while(m<x)
        m*=10;
    int ar=a%m, aq=a/m;
    int br=b%m, bq=b/m;
    if (ar>x)
        aq++;
    if(br<x)
        bq--;
    return bq-aq+1;
}
int main(){
    ifstream inputdata("Get gift/inputdata.txt");
    ofstream outputdata("Get gift/outputdata.txt");
    int t;
    inputdata>>t;
    for(int i=0; i<t; i++){
        int x, a, b;
        inputdata>>x>>a>>b;
        int result=getGift(x, a, b);
        outputdata<<result<<endl;
        cout<<result<<endl;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}
