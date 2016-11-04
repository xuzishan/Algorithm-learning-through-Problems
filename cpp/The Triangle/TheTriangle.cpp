#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
int theTriangle(int *a, int n){
	int *m=new int[n*n],r;
	m[0]=a[0];
	for(int i=1;i<n;i++)
		for(int j=0;j<=i;j++)
			if(j==0)m[i*n+j]=m[(i-1)*n+j]+a[i*n+j];
			else if(j==i)m[i*n+j]=m[(i-1)*n+j-1]+a[i*n+j];
			else m[i*n+j]=(m[(i-1)*n+j]>m[(i-1)*n+j-1]?m[(i-1)*n+j]:m[(i-1)*n+j-1])+a[i*n+j];
	r= *(max_element(m+(n-1)*n,m+(n-1)*n+n));
	delete[] m;
	return r;
}
int main(){
	ifstream inputdata("The Triangle/inputdata.txt");
	ofstream outputdata("The Triangle/outputdata.txt");
	int n,*a;
	inputdata>>n;
	a=new int[n*n];
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			inputdata>>a[i*n+j];
	int result=theTriangle(a,n);
	outputdata<<result<<endl;
	cout<<result<<endl;
	delete[] a;
	inputdata.close();outputdata.close();
	return 0;
}