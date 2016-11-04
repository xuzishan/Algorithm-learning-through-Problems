#include <fstream>
#include <string>
#include <hash_map>
#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
struct Project{//项目数据类型
    string name;
    int number;
    Project(string aname="", int n=0):name(aname),number(n){}//构造函数
};
bool operator==(const Project& a, const Project& b){//用来在项目集合中查找的比较运算
    return a.name==b.name;
}
bool operator<(const Project& a, const Project& b){//用来对项目集合排序的比较运算
    if(a.number>b.number)
        return true;
    if(a.number<b.number)
        return false;
	return a.name<b.name;
}
ostream& operator<<(ostream& out, const Project& a){//用来输出项目集合中元素的运算
    out<<a.name<<" "<<a.number;
    return out;
}
struct Student{
    string pName;
    bool deleted;
    Student(string projectName="", bool isDeleted=false):pName(projectName), deleted(isDeleted){}
};
set<Project,less<Project>> openSource(vector<string> &a){
    hash_map<string,Student> students;
    set<Project,less<Project> > projects;
	int n=a.size(), i=0;
	while(i<n){
		Project project(a[i++]);
		while(i<n&&a[i][0]>='a'&&a[i][0]<='z'){
			string userid=a[i];
			Student student=students[userid];
			if(student.pName==""){
				students[userid]=Student(project.name, false);
				project.number++;
			}else if((student.pName!=project.name)&&(!student.deleted)){
                set<Project>::iterator p=find(projects.begin(),projects.end(),Project(student.pName));
				Project	q(p->name, p->number-1);
                projects.erase(p);
				projects.insert(q);
			}
			i++;
		}
		projects.insert(project);
	}
	return projects;
}
int main(){
    ifstream inputdata("Open Source/inputdata.txt");
    ofstream outputdata("Open Source/outputdata.txt");
    string s="";
	getline(inputdata, s);
	while(s!="0"){
		vector<string> a;
		while(s!="1"){
			a.push_back(s);
			getline(inputdata, s);
		}
		set<Project,less<Project>> projects=openSource(a);
		copy(projects.begin(),projects.end(),ostream_iterator<Project>(outputdata, "\n"));
		copy(projects.begin(),projects.end(),ostream_iterator<Project>(cout, "\n"));
		getline(inputdata,s);
	}
    inputdata.close();outputdata.close();
    return 0;
}