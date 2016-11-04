//
//  GoldCoins.cpp
//  Algorithms
//
//  Created by 徐子珊 on 14-9-24.
//  Copyright (c) 2014年 徐子珊. All rights reserved.
//

#include <fstream>
#include <iostream>
using namespace std;
int goldCins(int N){
    int coins=0, k=1, days=0;
    while(days+k<=N){
        coins+=k*k;
        days+=k;
        k++;
    }
    int j=N-days;
    coins+=k*j;
    return coins;
}
int main(){
    ifstream inputdata("Gold Coins/inputdata.txt");
    ofstream outputdata("Gold Coins/outputdata.txt");
    int N;
    inputdata>>N;
    while(N){
        int result=goldCins(N);
        outputdata<<N<<" "<<result<<endl;
        cout<<N<<" "<<result<<endl;
        inputdata>>N;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}