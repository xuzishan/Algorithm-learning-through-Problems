//
//  Binary Search Heap Construction.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/3/2.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
struct Element{
	string label;
	int priority;
	Element(string s, int p): label(s), priority(p){}
};
bool operator<(const Element &a, const Element &b){
	return a.priority<b.priority;
}
struct Tree{
	Element ele;
	Tree *left, *right;
	Tree(Element e, Tree* l=NULL, Tree* r=NULL): ele(e), left(l), right(r){}
};
void insert(Tree *t, Element e){
	Tree *x=t, *current;
	while(x!=NULL){
		current=x;
		if(e.label<x->ele.label)
			x=x->left;
		else
			x=x->right;
	}
	if (e.label<current->ele.label)
		current->left=new Tree(e);
	else
		current->right=new Tree(e);
}
Tree* makeTree(vector<Element> &element){
	priority_queue<Element> Q(element.begin(), element.end());
	Tree *root;
	Element ele=Q.top(); Q.pop();
	root=new Tree(ele);
	while(!Q.empty()){
		ele=Q.top();Q.pop();
		insert(root,ele);
	}
	return root;
}
void toString(Tree *t, string &s){
	if(t==NULL)
		return;
	ostringstream so;
	s+='(';
	if(t->left)
		toString(t->left, s);
	s+=(t->ele.label+'/');
	so<<t->ele.priority;
	s+=so.str();
	if(t->right)
		toString(t->right, s);
	s+=')';
}
int main(){
    ifstream inputdata("Binary Search Heap Construction/inputdata.txt");
    ofstream outputdata("Binary Search Heap Construction/outputdata.txt");
	int n;
	inputdata>>n;
	while(n>0){
		string s;
		getline(inputdata, s);s=s.substr(1);
		int i=s.find('/');
		while(i>-1){
			s.replace(i, 1, 1,' ');
			i=s.find('/');
		}
		vector<Element> element;
		istringstream scanner(s);
		for (int i=0; i<n; i++){
			string c;
			int x;
			scanner>>c>>x;
			element.push_back(Element(c, x));
		}
		Tree *t=makeTree(element);
		s="";
		toString(t, s);
		outputdata<<s<<endl;
		cout<<s<<endl;
		inputdata>>n;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}