//
//  WhatFixNotation.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/3/11.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;
class Expression{
private:
	char ope;
	Expression* lopd;
	Expression* ropd;
public:
	Expression(char op, Expression* l=NULL, Expression* r=NULL):ope(op), lopd(l), ropd(r){}
	~Expression();
	void postOrder(string &s);
};
Expression::~Expression(){
	if (lopd) delete lopd;
	if (ropd) delete ropd;
}
void Expression::postOrder(string &s){
	if (lopd)
		lopd->postOrder(s);
	if(ropd)
		ropd->postOrder(s);
	s=s+ope+" ";
}
string whatFixNotation(string &prefix){
	stack<Expression*> opds;
	string s(prefix.rbegin(), prefix.rend());
	istringstream strstr(s);
	char item;
	string operators="$*/+-&|!";
	while (strstr>>item) {
		Expression *left=NULL, *right=NULL;
		if (operators.find(item)<8){
			if (item!='!'){
				left=opds.top();
				opds.pop();
			}
			right=opds.top();
			opds.pop();
		}
		opds.push(new Expression(item, left, right));
	}
	Expression* r=opds.top();opds.pop();
	string postfix;
	r->postOrder(postfix);
	delete r;
	return postfix;
}
int main(){
    ifstream inputdata("WhatFix Notation/inputdata.txt");
    ofstream outputdata("WhatFix Notation/outputdata.txt");
    string infix, prefix;
    while (getline(inputdata, infix)) {
        string postfix;
        getline(inputdata, prefix);
        postfix=whatFixNotation(prefix);
        outputdata<<"INFIX    => "<<infix<<endl;
        outputdata<<"PREFIX   => "<<prefix<<endl;
        outputdata<<"POSTFIX  => "<<postfix<<endl;
        cout<<"INFIX    => "<<infix<<endl;
        cout<<"PREFIX   => "<<prefix<<endl;
        cout<<"POSTFIX  => "<<postfix<<endl;
    }
    inputdata.close();
	outputdata.close();
    return 0;
}