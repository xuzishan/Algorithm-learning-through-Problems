#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>
#include <bitset>
#include <cassert>
#include <functional>
#include <cmath>
#include <limits>
using namespace std;
bool prime(size_t x){
	//int a=sqrt(double(x));
	for(size_t i=2; i<x; i++){
		if(!x%i)
			return false;
	}
	return true;
}
int main(){
	ifstream f("utility/prime/prime0.txt");
	bitset<100000> *a=new bitset<100000>();//1410065408
	f>>(*a);
	f.close();
	delete a;
	return 0;
}
