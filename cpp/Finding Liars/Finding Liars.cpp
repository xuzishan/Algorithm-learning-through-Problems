//
//  Finding Liars.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/12/23.
//  Copyright © 2015年 xu_zishan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
vector<int> findLiars(vector<int> &a, int t){
	vector<int> r;
	int n=a.size(), i;
	for(i=0; i<n; i++)
		if (a[i]==1)
			break;
	if(i>=n)
		return r; 
	for(int i=0;i<n; i++){
		int count=0;
		int j=i;
		while(a[j]==0)
			j=(j+1)%n;
		count++;
		j=(i-1+n)%n;
		if(a[j]==1){
			count++;
			j=(j-1+n)%n;
			while(a[j]==0){
				count++;
				j=(j-1+n)%n;
			}
		}
		if(count>t)
			r.push_back(i);
	}
	return r;
}
int main(){
    ifstream inputdata("Finding Liars/inputdata.txt");
    ofstream outputdata("Finding Liars/outputdata.txt");
	int T;
	inputdata>>T;
	for(int i=0; i<T; i++){
		int n, t;
		inputdata>>n>>t;
		vector<int> a;
		for(int i=0; i<n; i++){
			int x;
			inputdata>>x;
			a.push_back(x);
		}
		vector<int> result=findLiars(a, t);
		if(result.empty()){
			outputdata<<0<<" "<<0<<endl;
			cout<<0<<" "<<0<<endl;
		}else{
			outputdata<<result.size()<<" "<<result[0]+1<<endl;
			cout<<result.size()<<" "<<result[0]+1<<endl;
		}
	}
    inputdata.close();
    outputdata.close();
    return 0;
}