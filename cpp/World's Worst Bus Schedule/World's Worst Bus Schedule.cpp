//
//  World's Worst Bus Schedule.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int sum(vector<int> &a, int start, int end){
    int s=0;
    for (int i=start;  i<=end; i++) {
        s+=a[i];
    }
    return s;
}
int WorldsWorstBusSchedule(vector<vector<int>> durations, int arrival){
    int N=int(durations.size());
    vector<int> time(N);
    for (int i=0; i<N; i++) {
        int mi=int(durations[i].size());
        int Ti=sum(durations[i], 0, mi-1);
        int Ri=arrival%Ti;
        int k=0, sigm=0;
        while (sigm-Ri<0)
            sigm+=durations[i][k++];
        time[i]=sum(durations[i], 0, k-1)-Ri;
    }
    return *min(time.begin(), time.end());
}
int main(){
    ifstream inputdata("World's Worst Bus Schedule/inputdata.txt");
    ofstream outputdata("World's Worst Bus Schedule/outputdata.txt");
    string s;
    getline(inputdata, s);
    while (s!="ENDOFINPUT") {
        istringstream strstream(s);
        string str;
        strstream>>str;//略过START
        int N;
        strstream>>N;
        vector<vector<int>> durations(N);
        for (int i=0; i<N; i++) {
            getline(inputdata, s);
            strstream=istringstream(s);
            int x;
            while (strstream>>x) {
                durations[i].push_back(x);
            }
        }
        int arrival;
        inputdata>>arrival;
        int result=WorldsWorstBusSchedule(durations, arrival);
        outputdata<<result<<endl;
        cout<<result<<endl;
        getline(inputdata, str);//断行
        getline(inputdata, str);//略过END
        getline(inputdata, s);//读取新的案例首行
    }
    inputdata.close();
    outputdata.close();
    return 0;
}