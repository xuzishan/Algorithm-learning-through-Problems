#include<fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <iterator>
using namespace std;
class Browser{
    stack<string> forwardStack, backStack;
    string currentUrl;
public:
    Browser(string url):currentUrl(url){}
private:
    bool back(){
        if(!backStack.empty()){
            forwardStack.push(currentUrl);
            currentUrl=backStack.top();
            backStack.pop();
            return true;
        }
        return false;
    }
    bool forward(){
        if(!forwardStack.empty()){
            backStack.push(currentUrl);
            currentUrl=forwardStack.top();
            forwardStack.pop();
            return true;
        }
        return false;
    }
    void visit(string url){
        backStack.push(currentUrl);
        currentUrl=url;
        while (!forwardStack.empty())
            forwardStack.pop();
    }
public:
	vector<string> webNavigation(vector<string> &commands){
		int n=commands.size();
		vector<string> result;
		for (int i=0; i<n; i++) {
			istringstream strstr(commands[i]);
			string cmd, aline="Ignored";
			strstr>>cmd;
			if (cmd=="BACK" && back())
				aline=currentUrl;
			else if (cmd=="FORWARD" && forward())
				aline=currentUrl;
			else if (cmd=="VISIT"){
				string url;
				strstr>>url;
				visit(url);
				aline=currentUrl;
			}
			result.push_back(aline);
		}
		return result;
	}
};
int main(){
    ifstream inputdata("Web Navigation/inputdata.txt");
    ofstream outputdata("Web Navigation/outputdata.txt");
    string command;
	vector<string> cmds;
    getline(inputdata,command);
    while (command!="QUIT") {
		cmds.push_back(command);
        getline(inputdata, command);
    }
    Browser browser("http://www.acm.org/");
	vector<string> result=browser.webNavigation(cmds);
	copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
	copy(result.begin(), result.end(), ostream_iterator<string>(outputdata, "\n"));
    inputdata.close();
    outputdata.close();
    return 0;
}