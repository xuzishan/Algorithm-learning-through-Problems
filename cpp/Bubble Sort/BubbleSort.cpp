#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void bublleSortRounds(int N, int K, int k, vector<int> &x, int &count){
	if(k>=K){
		int item=1;
		for(int i=0;i<K;i++)
			item=(item*x[i])%20100713;
		count=(count+item)%20100713;
		return;
	}
	int begin,end;
	if(k==0){
		begin=N-1;
		end=K;
	}else{
		begin=x[k-1]-1;
		end=K-k;
	}
	for(int p=begin;p>=end;p--){
		x[k]=p;
		bublleSortRounds(N, K, k+1, x, count);
	}
}
int main(){
	ifstream inputdata("Bubble Sort/inputdata.txt");
	ofstream outputdata("Bubble Sort/outputdata.txt");
	int T, N, K;
	inputdata>>T;
	for(int t=0; t<T; t++){
		inputdata>>N>>K;
		int count=0;
		vector<int> x=vector<int>(K);
		bublleSortRounds(N, K, 0, x, count);
		outputdata<<count<<endl;
        cout<<count<<endl;
	}
	inputdata.close();
    outputdata.close();
	return 0;
}