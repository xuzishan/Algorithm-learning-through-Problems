#include <fstream>
#include <iostream>
#include "../utility/PriorityQueue.h"
struct gift{//礼物类型
	int K;//礼物分类
	int L;//礼物重复出售次数
	size_t time;//购买礼物时间
};
bool operator ==(const gift &a, const gift &b){//查找时所需相等运算
	return a.K==b.K;
}
bool operator <(const gift &a, const gift &b){//计算优先级所需小于运算
	if(a.L<b.L)
		return true;
	if(a.L==b.L)
		return a.time<b.time;
	return false;
}
int davidShoping(const vector<int> &shops, const int m){//购物模拟
	int discard=0;
    size_t n=shops.size();
	PriorityQueue<gift> pocket;//包包
	int index;
    gift g;
	for(int i=0;i<n;i++){//进入每个店铺
		g.K=shops[i];g.L=1,g.time=n-i;//第i各店铺出售的礼物
		index=pocket.search(g);//查看包中是否有g
		if(index==-1)//还没有
			if(pocket.size()<m){//包中尚有空间
				pocket.push(g);//放进包中
			}else{//包满
				pocket.pop();
				pocket.push(g);
				discard++;//跟踪放弃礼物次数
			}
        else{//包中已有g
			g.L++;//增加重复次数
			pocket.replace(g, index);
        }
	}
	return discard;//返回结果
}int main(){
	ifstream inputdata("David shopping/inputdata.txt");
	ofstream outputdata("David shopping/outputdata.txt");
	int M, N, num=1;
	inputdata>>M>>N;//读取m，n
	while(M||N){//处理每个案例
		vector<int> shops=vector<int>(N);
		int i, result;
		for(i=0;i<N;i++)//读取每家店铺的礼物信息
			inputdata>>shops[i];
        result=davidShoping(shops,M);
		outputdata<<"Case "<<num<<": "<<result<<endl;//输出案例结果
        cout<<"Case "<<num++<<": "<<result<<endl;
        inputdata>>M>>N;
	}
	inputdata.close();
	outputdata.close();
	return 0;
}