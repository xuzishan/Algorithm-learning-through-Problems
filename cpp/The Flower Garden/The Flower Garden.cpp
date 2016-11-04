//
//  The Flower Garden.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int theFlowerGarden(int F, int K, vector<int> L, vector<int> I){
    int i=*(min_element(L.begin(), L.end()));
    int count=i;
    while (i<F) {
        int j;
        for (j=0; j<K; j++){
            if (i % I[j]==L[j])
                break;
        }
        if (j>=K)
            count++;
        i++;
    }
    return count;
}
int main(){
    ifstream inputdata("The Flower Garden/inputdata.txt");
    ofstream outputdata("The Flower Garden/outputdata.txt");
    int F, K;
    inputdata>>F>>K;
    vector<int> L, I;
    for (int j=0; j<K; j++) {
        int lj, ij;
        inputdata>>lj>>ij;
        L.push_back(lj-1);
        I.push_back(ij);
    }
    int result=theFlowerGarden(F, K, L, I);
    outputdata<<result<<endl;
    cout<<result<<endl;
    inputdata.close();
    outputdata.close();
    return 0;
}