//
//  tobefirst.cpp
//  Algorithms
//
//  Created by 徐子珊 on 14-2-10.
//  Copyright (c) 2014年 徐子珊. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <set>
using namespace std;
struct Triple{
    int yl,yu,x;
    Triple(int y1, int y2, int xx):yl(y1),yu(y2),x(xx){}
};
struct Pair{
    int height;
    bool right;
    Pair(int h=0, bool r=true):height(h), right(r){}
};
bool operator==(const Pair& a, const Pair& b){
    return a.height==b.height;
}
bool operator>(const Pair& a, const Pair& b){
    return a.height>b.height;
}
vector<set<Pair, greater<Pair> > > makeMatrix(vector<Triple> &a, int N, int K){
    int M=a.size();
    vector<set<Pair, greater<Pair> > > line(N, set<Pair, greater<Pair> >());
    for(int i=0; i<M; i++){
        int xl=a[i].yl, xr=a[i].yu, y=a[i].x;
        line[xl-1].insert(Pair(y, true));
        line[xr-1].insert(Pair(y, false));
    }
    return line;
}
list<Triple> path(vector<set<Pair, greater<Pair> > >& line, int K){
    list<Triple> pathk;
    int yu=1000000, yl, j=K-1;
    set<Pair>::iterator current=line[j].begin();
    while(current!=line[j].end()){
        yl=current->height;
        pathk.push_front(Triple(yl, yu, j+1));
        (current->right)?(j++):(j--);
        current=line[j].find(Pair(yl));
        current++;
        yu=yl;
    }
    pathk.push_front(Triple(0, yu, j+1));
    return pathk;
}
list<Triple> backPath(vector<set<Pair, greater<Pair> > >& line){
    list<Triple> back_path;
    int yl=0, yu, j=0;
    set<Pair>::iterator current=line[j].end();
    if(current!=line[j].begin()) current--;
    while (current!=line[j].begin()) {
        yu=current->height;
        back_path.push_back(Triple(yl, yu, j+1));
        (current->right)?(j++):(j--);
        current=line[j].find(Pair(yu));
        if(current!=line[j].begin()) current--;
        yl=yu;
    }
    back_path.push_back(Triple(yl, 1000000, j+1));
    return back_path;
}
bool ok(list<Triple>& p1, list<Triple>& p2){//判断是否可画一横线使度熊第一出场
    for(list<Triple>::iterator it1=p1.begin();it1!=p1.end();it1++){
        for(list<Triple>::iterator it2=p1.begin();it2!=p1.end();it2++)
            if((abs(it1->x-it2->x)==1)&&
               ((it1->yl<=it2->yl&&it2->yl<=it1->yu&&it1->yu<<it2->yu)||
                (it2->yl<=it1->yl&&it1->yl<=it2->yu&&it2->yu<=it1->yu)))
                return true;
    }
    return false;
}
string toBeFirst(vector<set<Pair, greater<Pair> > >& line, int K){
    list<Triple> pathk=path(line, K);
    if((--(pathk.end()))->x==1) return "Yes";
    list<Triple> bPath1=backPath(line);
    return ok(pathk, bPath1)?"Yes":"No";
}
int main(){
    ifstream inputdata("/Users/xu_zishan/Documents/laboratory/laboratory/cpp/To be First/inputdata.txt");
    ofstream outputdata("/Users/xu_zishan/Documents/laboratory/laboratory/cpp/To be First/outputdata.txt");
    int T;
    inputdata>>T;//读取案例数
    for(int t=0; t<T; t++){//处理每一个案例
        int N, M, K;
        inputdata>>N>>M>>K;
        vector<Triple> a;
        for(int i=0; i<M; i++){
            int xl, xr, y;
            inputdata>>xl>>xr>>y;
            a.push_back(Triple(xl, xr, y));
        }
        vector<set<Pair, greater<Pair> > > line=makeMatrix(a, N, K);
        string aline=toBeFirst(line, K);
        outputdata<<aline<<endl;
        cout<<aline<<endl;
    }
    inputdata.close();
    outputdata.close();
}