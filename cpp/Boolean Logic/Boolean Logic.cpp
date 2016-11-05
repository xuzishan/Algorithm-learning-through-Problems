//
//  Boolean Logic.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/11/8.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <hash_map>
#include <set>
#include <stack>
#include <bitset>
using namespace std;
struct Proposition{
    Proposition *left;
    Proposition *right;
    string oper;
    int value;
    Proposition(string op, Proposition *l=NULL, Proposition *r=NULL):oper(op), left(l), right(r){}
};
class  TruthTable {
    hash_map<char, int> symble;
    vector<int> position;
    Proposition *proposition;
    int length;
	vector<bitset<32>> appoints;
    vector<char> values;
private:
	void calculate(Proposition *propo, bitset<32> appoint);
	void getValue(Proposition* propo);
	void subsetTree(bitset<32> appoint, int k);
public:
    TruthTable(string &s);
	vector<string> booleanLogic();
};
TruthTable::TruthTable(string &s){
	symble=hash_map<char, int>();
    position=vector<int>();
    length=s.length();
	appoints=vector<bitset<32>>();
    set<char> sym=set<char>();
    stack<Proposition*> operands = stack<Proposition*>();
    stack<string> operators = stack<string>();
    istringstream scanner=istringstream(s);
    string item;
    int p = -1;
    while (scanner>>item){
		p++;
        if (item>="a" && item<="z"){
			sym.insert(item[0]);
            operands.push(new Proposition(item));
            position.push_back(p++);
            continue;
        }
        if (item=="(") {
            operators.push(item);
            p++;
            continue;
        }
        string t=operators.top();
        while (t != "(") {
            operators.pop();
            Proposition *l=NULL;
            Proposition *r=operands.top(); operands.pop();
            if (t != "!") {
                l=operands.top();
                operands.pop();
            }
            operands.push(new Proposition(t, l, r));
            t=operators.top();
        }
        if (item==")") {
            operators.pop();
            p++;
        }else{
            operators.push(item);
            position.push_back(p+item.length()/2);
			p+=item.length();
        }
    }
    proposition=operands.top(); operands.pop();
	int i=0;
	for (set<char>::iterator p=sym.begin(); p!=sym.end(); p++, i++) {
        symble[*p]=i;
    }
}
void TruthTable::calculate(Proposition *propo, bitset<32> appoint){
    if (propo->left==NULL && propo->right==NULL) {
		const int n=symble.size();
        propo->value = appoint[symble[propo->oper[0]]];
        return;
    }
    if (propo->oper == "!") {
        calculate(propo->right, appoint);
        propo->value = (propo->right->value)==1 ? 0 : 1;
        return;
    }
    if (propo->oper == "&") {
        calculate(propo->left, appoint);
        calculate(propo->right, appoint);
        propo->value = propo->left->value & propo->right->value;
        return;
    }
    if (propo->oper == "|") {
        calculate(propo->left, appoint);
        calculate(propo->right, appoint);
        propo->value = propo->left->value | propo->right->value;
        return;
    }
    if (propo->oper == "-->") {
        calculate(propo->left, appoint);
        calculate(propo->right, appoint);
        int value1 = propo->left->value==1 ? 0 : 1;
        propo->value = value1 | propo->right->value;
        return;
    }
    if (propo->oper == "<->") {
        calculate(propo->left, appoint);
        calculate(propo->right, appoint);
        int value1 = propo->left->value==1 ? 0 :1;
        int value2 = propo->right->value==1 ? 0 : 1;
        int value3 = value1 & value2;
        int value4 = propo->left->value & propo->right->value;
        propo->value=value3 | value4;
        return;
    }
}
void TruthTable::getValue(Proposition* propo){
    if (propo->left != NULL)
		getValue(propo->left);
	values.push_back('0'+propo->value);
    if (propo->right != NULL)
        getValue(propo->right);
}
void TruthTable::subsetTree(bitset<32> appoint, int k){
	if (k==symble.size()){
		appoints.push_back(bitset<32>(appoint));
		return;
	}
	for (int i=0; i<2; i++) {
		appoint[k]=i;
		subsetTree(appoint, k+1);
	}
}
vector<string> TruthTable::booleanLogic(){
	bitset<32> x;
	subsetTree(x, 0);
    string valueLine=string(length, ' ');
    vector<string> table;
	for (int i=0; i<appoints.size(); i++) {
        values=vector<char>();
        calculate(proposition, appoints[i]);
        getValue(proposition);
        for (int i=0; i<values.size(); i++)
            valueLine[position[i]]=values[i];
        table.push_back(valueLine);
    }
    return table;
}

int main(){
    ifstream inputdata("Boolean Logic/inputdata.txt");
    ofstream outputdata("Boolean Logic/outputdata.txt");
	string s;
	while(getline(inputdata, s)){
		TruthTable booleanT(s);
		vector<string> a=booleanT.booleanLogic();
		outputdata<<s<<endl;
		cout<<s<<endl;
		for (int i=0; i<a.size(); i++) {
			outputdata<<a[i]<<endl;
			cout<<a[i]<<endl;
		}
	}
    inputdata.close();
    outputdata.close();
    return 0;
}