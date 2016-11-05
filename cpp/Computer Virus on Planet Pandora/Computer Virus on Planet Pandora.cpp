//
//  Computer Virus on Planet Pandora.cpp
//  laboratory
//
//  Created by 徐子珊 on 16/3/23.
//  Copyright © 2016年 xu_zishan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
string extract(string &program){
	string program1;
	int i=0, n=program.length();
	while(i<n){
		while(i<n&&program[i]!='[')
			program1+=program[i++];
		if (i>=n)
			return program1;
		int q=0;
		i++;
		while(program[i]>='0'&&program[i]<='9')
			q=q*10+(program[i++]-'0');
		string str(q, program[i++]);
		program1+=str;
		i++;
	}
	return program1;
}
int computerVirusOnPlanetPandora(vector<string> &virus, string &program){
	int n=virus.size();
	int count=0;
	string program1=extract(program);
	for(int i=0; i<n; i++){
		string virus1(virus[i].rbegin(), virus[i].rend());
		if(program1.find(virus[i])!=string::npos||
			program1.find(virus1)!=string::npos)
			count++;
	}
	return count;
}
int main(){
    ifstream inputdata("Computer Virus on Planet Pandora/inputdata.txt");
    ofstream outputdata("Computer Virus on Planet Pandora/outputdata.txt");
	int T;
	inputdata>>T;
	for(int t=0; t<T; t++){
		int n;
		inputdata>>n;
		vector<string> virus(n);
		for(int i=0; i<n; i++)
			inputdata>>virus[i];
		string program;
		inputdata>>program;
		int result=computerVirusOnPlanetPandora(virus, program);
		outputdata<<result<<endl;
		cout<<result<<endl;
	}
    inputdata.close();
	outputdata.close();
	return 0;
} 