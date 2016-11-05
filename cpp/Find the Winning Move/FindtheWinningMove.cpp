//
//  FindtheWinningMove.cpp
//  Algorithms
//
//  Created by 徐子珊 on 13-7-7.
//  Copyright (c) 2013年 徐子珊. All rights reserved.
//
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;
//class TicTacToe;
//bool checkrow(int i, int targ){//检测targ所示格局是否在第i行赢
//    int v=15<<(i*4);
//    return v==(targ&v);
//}
//bool checkcol(int j, int targ){//检测targ所示格局是否在第j列赢
//    int v=4369<<j;
//	return v==(targ&v);
//}
//bool checkdiag(int targ){//检测targ所示格局是否在主对角线赢
//    int v=33825;
//    return v==(targ&v);
//}
//bool checkdiag1(int targ){//检测targ所示格局是否在次对角线赢
//    int v=4680;
//    return v==(targ&v);
//}
//class Player{//玩家类
//    bool win;//赢标志
//    int pattern;//自家格局
//    int initp;//自家初始格局
//public:
//    Player(int p=0):win(false),initp(p),pattern(p){}
//    void place(int i, int j);//在第i行第j列处下子
//    void clear(int i, int j);//清除第i行第j列处棋子
//    void reset();//用自家初始格局重置
//    void reset(int p);//用格局参数重置
//    bool isWin(){return win;}//检测赢标志
//    friend void explore(TicTacToe &game, int k);//探索一局棋
//};
//void Player::place(int i, int j){
//    int v=1;
//    v=v<<(i*4+j);
//    pattern=pattern|v;//设置格局对应位为1
//    win=checkrow(i, pattern)||checkcol(j, pattern)||checkdiag(pattern)||checkdiag1(pattern);
//}
//void Player::clear(int i, int j){
//    int v=1;
//    v=v<<(i*4+j);
//    v=~v;//取反
//    pattern=pattern&v;//清除格局对应位上的1
//}
//void Player::reset(){
//    pattern=initp;
//    win=false;
//}
//void Player::reset(int p){
//    pattern=initp=p;
//    win=false;
//}
//bool checkdiag1(bitset<16> &targ){//检测targ所示格局是否在次对角线赢
//    bitset<16> v=4680;
//    return v==(targ&v);
//}
//class TicTacToe {//一字棋类
//    Player x, o;//两个玩家
//    vector<pair<int, int> > hole;//棋盘中可下子的棋眼
//    int p[16];//下子顺序
//    int n;//可下子数目
//    bool draw;//平局标志
//    bool forceWin;//x必赢标志
//public:
//    pair<int, int> winMove;//必赢首步
//    TicTacToe(string a[4]);//构造函数
//    void oneTurn(int k);//第k轮
//    void restore(int k);//回溯前恢复格局
//    void reset();//重置
//    bool xIsWin(){return forceWin;}//检测x必赢标志
//    friend void findWinningMove(TicTacToe &game);//回溯搜索必赢首步
//    friend void explore(TicTacToe &game, int k);
//};
//TicTacToe::TicTacToe(string a[4]){
//    int xinit=0,oinit=0;
//    n=0;
//    for(int i=0,t=0;i<4;i++)
//        for(int j=0;j<4;j++){
//            if(a[i][j]=='.'){//记录可下子棋眼
//                hole.push_back(make_pair(i,j));
//                p[t++]=n++;
//                continue;
//            }
//            int k=i*4+j,v=1;
//            v=v<<k;
//            if(a[i][j]=='x')//跟踪x初始格局
//                xinit=xinit|v;
//            else//跟踪o初始格局
//                oinit=oinit|v;
//        }
//    x.reset(xinit);//初始化x玩家
//    o.reset(oinit);//初始化o玩家
//    forceWin=draw=false;//初始化各标志
//    winMove=hole[p[0]];//初始化必赢首步
//}
//void TicTacToe::oneTurn(int k){//第k轮
//    int i=hole[p[k]].first,j=hole[p[k]].second;
//    if (k%2==0)//轮到x玩家
//        x.place(i, j);
//    else//轮到o玩家
//        o.place(i, j);
//}
//void TicTacToe::restore(int k){//恢复第k轮前格局
//    int i=hole[p[k]].first,j=hole[p[k]].second;
//    if (k%2==0)
//        x.clear(i, j);
//    else
//        o.clear(i, j);
//}
//void TicTacToe::reset(){
//    x.reset();
//    o.reset();
//    draw=false;
//    forceWin=draw=false;
//    winMove=hole[p[0]];
//}
//void explore(TicTacToe &game, int k){
//    int n=game.n;
//    if (game.o.isWin()){//上一步o玩家赢，退出
//        return;
//    }
//    if(game.x.isWin()){//上一步x玩家赢，准备x的另一种走法
//        game.x.win=false;
//        return;
//    }
//    if((k>=n)&&!game.x.isWin()&&!game.o.isWin()){//出现平局
//        game.draw=true;
//        return;
//    }
//    for(int i=k;i<n;i++){//上一步未能决出胜负，准备进一步探索，共有n-k个可能的走法
//        swap(game.p[k],game.p[i]);//决定下子的棋眼
//        game.oneTurn(k);//走一步
//        explore(game, k+1);//探索下一步
//        game.restore(k);//回溯前恢复格局
//        swap(game.p[k], game.p[i]);
//    }
//}
//void findWinningMove(TicTacToe &game){
//    int n=game.n;
//    for (int i=0; i<n; i++) {//n个可能的首步
//        swap(game.p[0], game.p[i]);
//        if (i>0&&!game.o.isWin()&&!game.draw) {//前一局x必赢
//            game.forceWin=true;
//            return;
//        }else{//或是第一局，或是前一局x非必赢
//            game.reset();//重置（x，o的格局恢复初始状态）
//            game.oneTurn(0);//x玩家走第一步
//            explore(game,1);//探索下一步
//            game.restore(0);//恢复各玩家格局
//            swap(game.p[0], game.p[i]);
//        }
//    }
//}
bool checkrow(int i, bitset<16> &targ){//检测targ所示格局是否在第i行赢
	bitset<16> v(15<<(i*4));
    return v==(targ&v);
}
bool checkcol(int j, bitset<16> &targ){//检测targ所示格局是否在第j列赢
    bitset<16> v(4369<<j);
	return v==(targ&v);
}
bool checkdiag(bitset<16> &targ){//检测targ所示格局是否在主对角线赢
    bitset<16> v(33825);
    return v==(targ&v);
}
bool checkdiag1(bitset<16> &targ){//检测targ所示格局是否在次对角线赢
    bitset<16> v(4680);
    return v==(targ&v);
}
class Player{//玩家类
    bool win;//赢标志
    bitset<16> pattern;//自家格局
    bitset<16> initp;//自家初始格局
    void place(int i, int j);//在第i行第j列处下子
    void clear(int i, int j);//清除第i行第j列处棋子
    void reset();//用自家初始格局重置
    void reset(bitset<16> &p);//用格局参数重置
public:
    Player(int p=0):win(false),initp(p),pattern(p){}
    bool isWin(){return win;}//检测赢标志
    friend class TicTacToe;//探索一局棋
};
void Player::place(int i, int j){
	pattern.set(i*4+j);//设置格局对应位为1
    win=checkrow(i, pattern)||checkcol(j, pattern)||checkdiag(pattern)||checkdiag1(pattern);
}
void Player::clear(int i, int j){
    pattern.reset(i*4+j);//清除格局对应位上的1
}
void Player::reset(){
    pattern=initp;
    win=false;
}
void Player::reset(bitset<16> &p){
    pattern=initp=p;
    win=false;
}
class TicTacToe {//一字棋类
    Player x, o;//两个玩家
    vector<pair<int, int> > hole;//棋盘中可下子的棋眼
    vector<int> p;//下子顺序
    int n;//可下子数目
    bool draw;//平局标志
    void oneTurn(int k);//第k轮
    void restore(int k);//回溯前恢复格局
    void reset();//重置
    void explore(int k);
public:
    pair<int, int> winMove;//必赢首步
    TicTacToe(vector<string> &a);//构造函数
    friend bool findWinningMove(TicTacToe &game);//回溯搜索必赢首步
};
TicTacToe::TicTacToe(vector<string> &a){
    bitset<16> xinit=0,oinit=0;
    n=0;
    for(int i=0,t=0;i<4;i++)
        for(int j=0;j<4;j++){
            if(a[i][j]=='.'){//记录可下子棋眼
                hole.push_back(make_pair(i,j));
				p.push_back(n++);
                continue;
            }
            int k=i*4+j;
            if(a[i][j]=='x')//跟踪x初始格局
                xinit.set(k);
            else//跟踪o初始格局
                oinit.set(k);
        }
    x.reset(xinit);//初始化x玩家
    o.reset(oinit);//初始化o玩家
    draw=false;//初始化各标志
    winMove=hole[p[0]];//初始化必赢首步
}
void TicTacToe::oneTurn(int k){//第k轮
    int i=hole[p[k]].first,j=hole[p[k]].second;
    if (k%2==0)//轮到x玩家
        x.place(i, j);
    else//轮到o玩家
        o.place(i, j);
}
void TicTacToe::restore(int k){//恢复第k轮前格局
    int i=hole[p[k]].first,j=hole[p[k]].second;
    if (k%2==0)
        x.clear(i, j);
    else
        o.clear(i, j);
}
void TicTacToe::reset(){
    x.reset();
    o.reset();
    draw=false;
    draw=false;
    winMove=hole[p[0]];
}
void TicTacToe::explore(int k){
    if (o.isWin()){//上一步o玩家赢，退出
        return;
    }
    if(x.isWin()){//上一步x玩家赢，准备x的另一种走法
        x.win=false;
        return;
    }
    if((k>=n)&&!x.isWin()&&!o.isWin()){//出现平局
        draw=true;
        return;
    }
    for(int i=k;i<n;i++){//上一步未能决出胜负，准备进一步探索，共有n-k个可能的走法
        swap(p[k],p[i]);//决定下子的棋眼
        oneTurn(k);//走一步
        explore(k+1);//探索下一步
        restore(k);//回溯前恢复格局
        swap(p[k], p[i]);
    }
}
bool findWinningMove(TicTacToe &game){
    int n=game.n;
    for (int i=0; i<n; i++) {//n个可能的首步
        swap(game.p[0], game.p[i]);
        if (i>0&&!game.o.isWin()&&!game.draw) {//前一局x必赢
            return true;
        }else{//或是第一局，或是前一局x非必赢
            game.reset();//重置（x，o的格局恢复初始状态）
            game.oneTurn(0);//x玩家走第一步
            game.explore(1);//探索下一步
            game.restore(0);//恢复各玩家格局
            swap(game.p[0], game.p[i]);
        }
    }
	return false;
}

int main(){
    ifstream inputdata("Find the Winning Move/inputdata.txt");
    ofstream outputdata("Find the Winning Move/outputdata.txt");
    char ch;
    inputdata>>ch;
    while(ch!='$'){
        string  s;
		vector<string> a(4);
        for(int i=0;i<4;i++)//读取案例初始棋局
            inputdata>>a[i];
        TicTacToe game(a);//创建棋局
        if (findWinningMove(game)) {//计算x必赢首步
            outputdata<<"("<<game.winMove.first<<","<<game.winMove.second<<")"<<endl;
            cout<<"("<<game.winMove.first<<","<<game.winMove.second<<")"<<endl;
        }else{
            outputdata<<"#####"<<endl;
            cout<<"#####"<<endl;
        }
        inputdata>>ch;
    }
    inputdata.close();
	outputdata.close();
	return 0;
}