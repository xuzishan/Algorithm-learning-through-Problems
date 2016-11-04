//
//  EnergyConversion.cpp
//  Algorithms
//
//  Created by 徐子珊 on 14-9-19.
//  Copyright (c) 2014年 徐子珊. All rights reserved.
//
#include <iostream>
#include <fstream>
using namespace std;
int energyConversion(int N, int M, int V, int K){
    int A=M, count=0;
    if(A>=N)
        return 0;
    if(A<V)
        return -1;
    do{
        int t=(A-V)*K;
        if(A>=t)
            return -1;
        A=t;
        count++;
    }while(A<N);
    return count;
}
int main(){
    ifstream inputdata("Energy Conversion/inputdata.txt");
    ofstream outputdata("Energy Conversion/outputdata.txt");
    int T;
    inputdata>>T;
    for(int t=0; t<T; t++){
        int N, M, V, K;
        inputdata>>N>>M>>V>>K;
        int result=energyConversion(N, M, V, K);
        outputdata<<result<<endl;
        cout<<result<<endl;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}