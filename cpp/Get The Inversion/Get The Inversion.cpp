//
//  Get The Inversion.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/22.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#include "../filepath.h"
int getTheInversion(vector<int> A){
    int N=int(A.size());
    int count=0;
    for (int j=N-1; j>0; j--)
        for (int i=0; i<j; i++)
            if(A[i]>A[j])
                count++;
    return count;
}

int main(){
    ifstream inputdata(basePath+"Get The Inversion/inputdata.txt");
    ofstream outputdata(basePath+"Get The Inversion/outputdata.txt");
    int N=0;
    inputdata>>N;
    while (N>0) {
        vector<int> A(N);
        for (int i=0; i<N; i++)
            inputdata>>A[i];
        int result=getTheInversion(A);
        cout<<result<<endl;
        outputdata<<result<<endl;
        inputdata>>N;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}