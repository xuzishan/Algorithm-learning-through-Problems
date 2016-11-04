#include <fstream>
#include <iostream>
#include <hash_set>
#include <sstream>
#include <string>
using namespace std;
int askaHelp(const string P, hash_set<const string> &T){
	int r,q,i,j,l,k;
	int *f;
	size_t n=P.length();
	f=new int[(n+1)*(n+1)];
	fill(f,f+(n+1)*(n+1),0);
	for(l=1;l<=n;l++){
		for(i=1;i<=n-l+1;i++){
			int length=l;
			j=i+l-1;
			q=INT_MAX;
			for(k=i-1;k<j;k++){
				if(T.find(P.substr(k,length--))!=T.end())
					if(q>f[i*(n+1)+k]+1)
						q=f[i*(n+1)+k]+1;
			}
			f[i*(n+1)+j]=q;
		}
	}
	r=f[n+1+n];
	delete []f;
	return r;
}

int main(){
	int n,r;
	string s;
	ifstream inputdata("Ask a Help/inputdata.txt");
	ofstream outputdata("Ask a Help/outputdata.txt");
	inputdata>>n;
	getline(inputdata,s,'\n');
	for(int i=0;i<n;i++){
		string P,t;
		istringstream s1;
		hash_set<const string> T;
		getline(inputdata,P,'\n');
		getline(inputdata,t,'\n');
		s1=istringstream(t);
		while(s1>>t)
			T.insert(t);
		r=askaHelp(P,T);
		if(r>P.length()){
			outputdata<<"Error"<<endl;
			cout<<"Error"<<endl;
		}else{
			outputdata<<r<<endl;
			cout<<r<<endl;
		}
	}
	inputdata.close();outputdata.close();
	return 0;
}
