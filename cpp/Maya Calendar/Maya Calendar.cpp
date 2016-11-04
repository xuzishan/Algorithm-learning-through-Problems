//
//  Maya Calendar.cpp
//  laboratory
//
//  Created by Ðì×ÓÉº on 16/4/4.
//  Copyright (c) 2016Äê xu_zishan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <hash_map>
using namespace std;
pair<string, int> a[]={make_pair("pop", 0), make_pair("no", 1), make_pair("zip", 2), make_pair("zotz", 3),
						make_pair("tzec", 4), make_pair("xul", 5), make_pair("yoxkin", 6), make_pair("mol", 7),
						make_pair("chen", 8), make_pair("yax", 9), make_pair("zac", 10), make_pair("ceh", 11),
						make_pair("mac", 12), make_pair("kankin", 13), make_pair("muan", 14), make_pair("pax", 15),
	                    make_pair("koyab", 16), make_pair("cumhu", 17), make_pair("uayet", 18)};
hash_map<string, int> Haab(a, a+19);
string Tzolkin[]={"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok",
					"chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};
string mayaCalendar(string &haab){
	istringstream s(haab);
	int NumberOfTheDay, Year;
	string Month;
	char dot;
	s>>NumberOfTheDay>>dot>>Month>>Year;
	int days=365*Year+20*Haab[Month]+NumberOfTheDay;
	Year=days/260;
	int r=days%260;
	int Number=(r%13)+1;
	string NameOfTheDay=Tzolkin[r%20];
	ostringstream os;
	os<<Number<<" "<<NameOfTheDay<<" "<<Year;
	return os.str();
}
int main(){
    ifstream inputdata("Maya Calendar/inputdata.txt");
    ofstream outputdata("Maya Calendar/outputdata.txt");
	int n;
	inputdata>>n;
	outputdata<<n<<endl;
	cout<<n<<endl;
	string haab;
	getline(inputdata, haab);
	for(int i=0; i<n; i++){
		getline(inputdata, haab);
		string tzolkin=mayaCalendar(haab);
		outputdata<<tzolkin<<endl;
		cout<<tzolkin<<endl;
	}
    inputdata.close();
    outputdata.close();
    return 0;
}