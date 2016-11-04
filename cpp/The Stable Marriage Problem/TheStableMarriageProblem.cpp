//
//  TheStableMarriageProblem.cpp
//  laboratory
//
//  Created by 徐子珊 on 14/12/31.
//  Copyright (c) 2014年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <set>
#include <hash_map>
#include <iterator>
using namespace std;
struct Male{
    string pref;
    size_t current;
    Male(string p=""):pref(p), current(0){}
};
struct Female{
    string pref;
    bool engaged;
    Female(string p=""): pref(p), engaged(false){}
};
struct Couple{
    char female, male;
    Couple(char f=' ', char m=' '):female(f), male(m){}
};
bool operator==(const Couple& a, const Couple& b){
    return a.female==b.female;
}
bool operator<(const Couple& a, const Couple& b){
    return a.male<b.male;
}
ostream& operator<<(ostream& out, const Couple& a){
    out<<a.male<<" "<<a.female;
    return out;
}
set<Couple, less<Couple> > stableMarriage(hash_map<char, Male>& M, hash_map<char, Female>& F){
    set<Couple, less<Couple> > A;
    queue<char> Q;
    hash_map<char, Male>::iterator a;
    for (a=M.begin(); a!=M.end(); a++)
        Q.push(a->first);
    while (!Q.empty()) {
        char m=Q.front();
        char f=M[m].pref[M[m].current++];
        if (!F[f].engaged) {
            A.insert(Couple(f, m));
            F[f].engaged=true;
            Q.pop();
        }else{
            set<Couple, less<Couple> >::iterator couple=find(A.begin(), A.end(), Couple(f));
            char m1=couple->male;
            if ((F[f].pref).find(m)<(F[f].pref).find(m1)) {
                A.erase(Couple(f, m1));
                A.insert(Couple(f, m));
                Q.pop();
                Q.push(m1);
            }
        }
    }
    return A;
}
int main(){
    ifstream inputdata("The Stable Marriage Problem/inputdata.txt");
    ofstream outputdata("The Stable Marriage Problem/outputdata.txt");
    int t;
    inputdata>>t;
    for (int i=0; i<t; i++) {
        int n;
        string aline;
        inputdata>>n;
        hash_map<char, Male> M;
        hash_map<char, Female> F;
        getline(inputdata, aline, '\n');
        getline(inputdata, aline, '\n');
        for(int j=0; j<n; j++){
            getline(inputdata, aline, '\n');
            char name=aline[0];
            string preference=aline.substr(2,n);
            M[name]=Male(preference);
        }
        for(int j=0; j<n; j++){
            getline(inputdata, aline, '\n');
            char name=aline[0];
            string preference=aline.substr(2,n);
            F[name]=Female(preference);
        }
        set<Couple, less<Couple> > A=stableMarriage(M, F);
        copy(A.begin(),A.end(),ostream_iterator<Couple>(outputdata, "\n"));
        outputdata<<endl;
        copy(A.begin(),A.end(),ostream_iterator<Couple>(cout, "\n"));
        cout<<endl;
    }
    inputdata.close();
	outputdata.close();
    return 0;
}