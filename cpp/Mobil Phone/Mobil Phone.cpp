//
//  Mobil Phone.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/22.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "../filepath.h"
struct command {
    int c, x, y, z, w;
    command(int a, int b=0, int c=0, int d=0, int e=0){
        this->c=a;
        this->x=b;
        this->y=c;
        this->z=d;
        this->w=e;
    }
};
vector<int> mobilPhone(const vector<command>& cmds){
    const int n=int(cmds.size());
    const int S=int(cmds[0].x);
    vector<vector<int>> tempere(S, vector<int>(S));
    vector<int> result;
    for (int k=1; k<n; k++) {
        const int cmd=cmds[k].c;
        if (cmd==1) {
            const int x=cmds[k].x, y=cmds[k].y, a=cmds[k].z;
            tempere[x][y]+=a;
            if (tempere[x][y]<0)
                tempere[x][y]=0;
        }else{
            const int L=cmds[k].x, B=cmds[k].y, R=cmds[k].z, T=cmds[k].w;
            int count=0;
            for (int i=L; i<=R; i++)
                for (int j=B; j<=T; j++)
                    count+=tempere[i][j];
            result.push_back(count);
        }
    }
    return result;
}
int main(){
    ifstream inputdata(basePath+"Mobil Phone/inputdata.txt");
    ofstream outputdata(basePath+"Mobil Phone/outputdata.txt");
    vector<command> cmds;
    int cmd;
    inputdata>>cmd;
    while (cmd != 3){
        switch (cmd) {
            case 0:
                int S;
                inputdata>>S;
                cmds.push_back(command(cmd, S));
                break;
            case 1:
                int X, Y, A;
                inputdata>>X>>Y>>A;
                cmds.push_back(command(cmd, X, Y, A));
                break;
            case 2:
                int L, B, R, T;
                inputdata>>L>>B>>R>>T;
                cmds.push_back(command(cmd, L, B, R, T));
            default:
                break;
        }
        inputdata>>cmd;
    }
    vector<int> result=mobilPhone(cmds);
    for (int i=0; i< result.size(); i++) {
        cout<<result[i]<<endl;
        outputdata<<result[i]<<endl;
    }
    inputdata.close();
    outputdata.close();
    return 0;
}