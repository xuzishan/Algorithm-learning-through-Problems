#include<fstream>
#include <iostream>
#include <algorithm>
using namespace std;
struct triple{
	int a, b, c;
};
class Triangle{//表示一般三角形的抽象类
protected:
	int left;//左边
	int right;//右边
	int bottom;//底边
public:
	Triangle(int a, int b, int c):left(a),right(b),bottom(c){}//构造函数
	virtual void rotate()=0;//顺时针旋转120度的纯虚函数
	virtual int getOutEdge()=0;//计算外边数据纯虚函数
	virtual bool check(Triangle* t)=0;//检测与相邻三角形是否相邻边相等的纯虚函数
	virtual int getNeighbor()=0;//计算相邻三角形相邻边的纯虚函数
};
class NormalTriangle:public Triangle{//底边朝下的三角形抽象类
public:
	NormalTriangle(triple& t):Triangle(t.a,t.b,t.c){}//构造函数
	void rotate(){//旋转虚函数的覆盖
		int tmp=left;
		left=bottom;
		bottom=right;
		right=tmp;
	}
};
class InverseTriangle:public Triangle{//底边朝上的三角形抽象类
public:
	InverseTriangle(triple& t):Triangle(t.a,t.c,t.b){}
	void rotate(){
		int tmp=bottom;
		bottom=left;
		left=right;
		right=tmp;
	}
};
class Triangle1:public NormalTriangle{//放在棋盘中第1个格子里的三角形类
public:
	Triangle1(triple& t):NormalTriangle(t){}
	int getOutEdge(){return left;}//覆盖计算外沿边的虚函数
	int getNeighbor(){return right;}//覆盖计算相邻三角形相邻边虚函数
	bool check(Triangle* t){return t->getNeighbor()==this->bottom;}//覆盖检测相邻三角形合法性虚函数
};
class Triangle3:public NormalTriangle{//放在第3个格子里的三角形类
public:
	Triangle3(triple& t):NormalTriangle(t){}
	int getOutEdge(){return right;}
	int getNeighbor(){return bottom;}
	bool check(Triangle* t){return t->getNeighbor()==this->left;}
};
class Triangle5:public NormalTriangle{//放在第5个格子里的三角形类
public:
	Triangle5(triple& t):NormalTriangle(t){}
	int getOutEdge(){return bottom;}
	int getNeighbor(){return left;}
	bool check(Triangle* t){return t->getNeighbor()==this->right;}
};
class Triangle2:public InverseTriangle{//放在第2个格子里的三角形类
public:
	Triangle2(triple& t):InverseTriangle(t){}
	int getOutEdge(){return bottom;}
	int getNeighbor(){return right;}
	bool check(Triangle* t){return t->getNeighbor()==this->left;}
};
class Triangle4:public InverseTriangle{//放在第4个格子里的三角形类
public:
	int getOutEdge(){return right;}
	int getNeighbor(){return left;}
	bool check(Triangle* t){return t->getNeighbor()==this->bottom;}
	Triangle4(triple& t):InverseTriangle(t){}
};
class Triangle6:public InverseTriangle{//放在第6个格子里的三角形类
public:
	Triangle6(triple& t):InverseTriangle(t){}
	int getOutEdge(){return left;}
	int getNeighbor(){return bottom;}
	bool check(Triangle* t){return t->getNeighbor()==this->right;}
};
class Game {//三角形游戏类
	triple *tr;
    Triangle *t[6];//表示环状棋盘的指针数组（用顶层抽象类指针实现多态性）
    int Max;//最大外缘边数值和
    int p[6];//表示三角形下标的数组
    void move();//得到三角形全排列
    void clear();//清理指针数组t
    void play(int k);//对排列好的6个三角形回溯合法的格局
public:
    Game(triple Tr[]);//构造函数
    int theTriangleGame();//计算合法格局最大外缘编之和
};
Game::Game(triple Tr[]):Max(INT_MIN){
	tr=Tr;
    for(int i=0;i<6;i++)
        p[i]=i;
}
void Game::move(){//用下标的环状全排列确定三角形的环状全排列
	t[0]=new Triangle1(tr[0]);//首元素是确定不变的
	t[1]=new Triangle2(tr[p[1]]);
	t[2]=new Triangle3(tr[p[2]]);
	t[3]=new Triangle4(tr[p[3]]);
	t[4]=new Triangle5(tr[p[4]]);
	t[5]=new Triangle6(tr[p[5]]);    
}
void Game::clear(){//清理三角形指针数组t的空间
    delete (Triangle1*)t[0];
    delete (Triangle2*)t[1];
    delete (Triangle3*)t[2];
    delete (Triangle4*)t[3];
    delete (Triangle5*)t[4];
    delete (Triangle6*)t[5];
}
void Game::play(int k){//回溯寻求合法格局中第k个三角形的摆法探索
	if(k>5){//六个三角形都已排好
		if(t[0]->check(t[5])){//得到合法格局
			int sum=0;
			for(int i=0;i<6;i++)//计算外缘边之和
				sum+=t[i]->getOutEdge();
			if(sum>Max)//跟踪最大者
				Max=sum;
		}
		return;
	}
	for(int i=1;i<=3;i++){
		t[k]->rotate();//旋转120度
		if(k>0&&!t[k]->check(t[k-1]))//与前一个格子中的三角形相邻边不吻合
			continue;//再旋转
		play(k+1);//与前者相邻边吻合，则进一步探索第k+1个三角形的合法摆放
	}
}
int Game::theTriangleGame(){//计算6个三角形的所有环状全排列
	do{
		move();
		play(0);
		clear();
	}while(next_permutation(p+1, p+6));
	return Max;
}
int main(){
	ifstream inputdata("The Triangle Game/inputdata.txt");
	ofstream outputdata("The Triangle Game/outputdata.txt");
	char ch='*';
 	while(ch!='$'){//读取一个案例数据
		triple tr[6];
		for(int i=0;i<6;i++)
			inputdata>>tr[i].a>>tr[i].b>>tr[i].c;
		Game g(tr);
		int max=g.theTriangleGame();//计算合法最大外缘值之和
        if(max>INT_MIN){//输出
			outputdata<<max<<endl;
            cout<<max<<endl;
        }else{
			outputdata<<"none"<<endl;
            cout<<"none"<<endl;
        }
		inputdata>>ch;
	}
	inputdata.close();outputdata.close();
	return 0;
}