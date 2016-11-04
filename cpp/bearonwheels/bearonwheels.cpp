#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
struct Action {
    int type;
    int score;
    bitset<32> prev;
    int stickn;
};
struct Group {
    bitset<32> members;
    int score;
};
class Game{
private:
	vector<Action> a;
	vector<Group> g;
	bitset<32> actions;
	int groups;
	int gValue;
	int currentValue;
	int sticks;
	int n, m, p;
	void groupScore(int k);
public:
	int value;
	Game(vector<Action> A, vector<Group> G, int N): a(A), g(G), actions(0), groups(INT_MIN), value(INT_MIN), gValue(0), currentValue(0), n(N), m(a.size()), sticks(0), p(g.size()){}
	void onWheels(int k);
};
void Game::groupScore(int k){
    if (k>=p) {
        if (gValue>groups) {
            groups=gValue;
        }
        return;
    }
    for (int i=0; i<2; i++) {
        if (i==0) {
            groupScore(k+1);
        }else if (g[k].members==(g[k].members&actions)) {
            gValue+=g[k].score;
            groupScore(k+1);
            gValue-=g[k].score;
        }
    }
}
void Game::onWheels(int k){
    if (k>=m) {
        if (sticks == n) {
            gValue=0;
            groupScore(0);
            currentValue+=groups;
            if (currentValue>value) {
                value=currentValue;
            }
        }
        return;
    }
    for (int i=0; i<2; i++) {
		i==1?actions.set(k): actions.reset(k);
        if (i>0) {
            if (a[k].type==2 && (a[k].prev & actions) == 0) {
                continue;
            }else if (a[k].type==3 && a[k].prev != (a[k].prev & actions)){
                continue;
            }
        }
        sticks+=i*(a[k].stickn);
        if (sticks>n) {
            sticks-=i*(a[k].stickn);
            continue;
        }
        currentValue+=i*(a[k].score);
        onWheels(k+1);
        currentValue-=i*(a[k].score);
        sticks-=i*(a[k].stickn);
    }
    actions[k]=0;
}
int main(){
    ifstream inputdata("bearonwheels/inputdata.txt");
    ofstream outputdata("bearonwheels/outputdata.txt");
    int t;
    inputdata>>t;
    for(int i=0;i<t;i++){
        int n, m, p, type, score, x, y, z;
        inputdata>>n>>m>>p;
        vector<Action> a(m);
        for(int k=0; k<m; k++){
            inputdata>>type;
            a[k].type=type;
        }
        for(int k=0; k<m; k++){
            inputdata>>a[k].stickn;
        }
        for(int k=0; k<m; k++){
            inputdata>>score;
            a[k].score=score;
        }
        vector<Group> g(p);
        for(int k=0;k<p;k++){
            inputdata>>x>>y;
            g[k].score=y;
            g[k].members=0;
            for(int j=0; j<x; j++){
                inputdata>>z;
				g[k].members.set(z-1);
            }
        }
        for(int k=0; k<m; k++){
            a[k].prev=0;
            if(a[k].type==1){
                int aj;
                for(int j=0; j<m; j++){
                    inputdata>>aj;
                    if(aj)
						a[k].prev.set(j);
                }
            }else if(a[k].type==2){
                int auv;
                for(int u=0;u<m;u++){
                    for(int v=0;v<m;v++){
                        inputdata>>auv;
                        if(auv){
							a[k].prev.set(u);
                            a[k].prev.set(v);
                        }
                    }
                }
            }
        }
		Game bear(a, g, n);
		bear.onWheels(0);
		outputdata<<bear.value<<endl;
		cout<<bear.value<<endl;
    }
    inputdata.close();outputdata.close();
    return 0;
}