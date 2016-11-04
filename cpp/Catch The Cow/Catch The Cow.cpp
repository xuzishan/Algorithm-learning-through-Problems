//
//  Catch The Cow.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
using namespace std;
pair<int, int> calculate(int x, int base=1){
    int t=0, p=base;
    while (p<x) {
        t++;
        p*=2;
    }
    if (p>x) {
        t--;
        p/=2;
    }
    return pair<int, int>(t, p);
}
int catchTheCow(int N, int K){
    if (N>=K) {
        return N-K;
    }
    pair<int, int> x=calculate(K, N);
    int q=x.first, n2q=x.second;
    if (n2q==K) {
        return q;
    }
    x=calculate(K);
    int p=x.first, one2p=x.second;
    x=calculate(N);
    int t=x.first, one2t=x.second;
    int a=q+K-n2q, b=q+1+2*n2q-K, c=(N-one2t)+(p-t)+(K-one2p);
    int d=(N-one2t)+(p-t+1)+(2*one2p-K), e=(2*one2t-N)+(p-t+1)+(K-one2p), f=(2*one2t-N)+(p-t)+(2*one2p-K);
    return min(a, min(b, min(c, min(d, min(e, f)))));
}

int main(){
    ifstream inputdata("Catch The Cow/inputdata.txt");
    ofstream outputdata("Catch The Cow/outputdata.txt");
    int T;
    inputdata>>T;
    for (int t=0; t<T; t++) {
        int N, K;
        inputdata>>N>>K;
        int result=catchTheCow(N, K);
        outputdata<<result<<endl;
        cout<<result<<endl;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}