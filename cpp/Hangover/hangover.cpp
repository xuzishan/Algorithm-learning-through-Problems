//
//  hangover.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/11/24.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
using namespace std;
int hangover(double c){
    int n=1;
    double length=0.0;
    while (length<c){
        length+=1.0/(n+1);
        n++;
    }
    if(length>c)
        n--;
    return n;
}
int main(){
    ifstream inputdata("Hangover/inputdata.txt");
    ofstream outpudata("Hangover/outputdata.txt");
    double c;
    inputdata>>c;
    while (c!=0.0) {
        int result=hangover(c);
        outpudata<<result<<" card(s)"<<endl;
        cout<<result<<" card(s)"<<endl;
        inputdata>>c;
    }
    inputdata.close();
	outpudata.close();
    return 0;
}