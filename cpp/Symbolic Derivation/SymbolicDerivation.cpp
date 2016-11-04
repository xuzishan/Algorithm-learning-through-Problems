//
//  SymbolicDerivation.cpp
//  laboratory
//
//  Created by 徐子珊 on 15/2/28.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <hash_map>
using namespace std;
#include <string.h>
pair<string, int> a[]={make_pair("(", 1), make_pair(")", 2),
					   make_pair("ln", 5), make_pair("*", 4),
					   make_pair("/", 4), make_pair("+", 3),
					   make_pair("-", 3), make_pair("@", -1),
					   make_pair("_", 6), make_pair("^", 7)};
hash_map<string, int> priority(a, a+10);
void preprocess(string &s){
    size_t n=s.length();
    for(int i=0; i<n; i++)
        if((i==0&&s[0]=='-')||(s[i]=='-'&&!isdigit(s[i-1])&&s[i-1]!='x'&&s[i-1]!=')'))
            s[i]='_';
	s+='@';
}
void fix(string &s){
    int i=0;
	while(i<s.length()) {
        if ((s[i]=='+'&&s[i+1]=='_')||(s[i]=='_'&&s[i+1]=='+')){
			s.erase(i, 1);
			s[i]='-';
		}else if(s[i]=='-'&&s[i+1]=='_'||s[i]=='_'&&s[i+1]=='-'){
			s[i]='+';
			s.erase(i+1, 1);
		}else if(s[i]=='_')
			s[i]='-';
        i++;
    }
}
class Expression{
protected:
    Expression *lopd;
    Expression *ropd;
public:
    string ope;
    Expression(string op, Expression *l=NULL, Expression *r=NULL):ope(op),lopd(l),ropd(r){}
    ~Expression(){
		if(lopd){
			delete lopd;
			lopd=NULL;
		}
		if(ropd){
			delete ropd;
			ropd=NULL;
		}
	}
	//string toString();
    virtual Expression* copy()=0;
	void toString(string &s);
	virtual Expression *derivation()=0;
};
//string Expression::toString(){
//    string s;
//    if(lopd){
//		bool add_parences=(priority[lopd->ope]>0) && ( priority[lopd->ope]<priority[ope]);
//		s+=add_parences ? ("("+lopd->toString()+")") : lopd->toString();
//	}
//    s+=ope;
//	if(ropd){
//		bool add_parences=(priority[ropd->ope]>0) && (priority[ropd->ope]<priority[ope]);
//		s+=add_parences ? ("("+ropd->toString()+")") : ropd->toString();
//	}
//    return s;
//}
void Expression::toString(string &s){
	string ls, rs;
    if(lopd){
		lopd->toString(ls);
		bool add_parences=(priority[lopd->ope]>0) && ( priority[lopd->ope]<priority[ope]);
		if(add_parences)
			ls='('+ls+')';
	}
	if(ropd){
		ropd->toString(rs);
		bool add_parences=(priority[ropd->ope]>0) && (priority[ropd->ope]<priority[ope]);
		if (add_parences)
			rs='('+rs+')';
	}
    s=ls+ope+rs;
}

class Const: public Expression{
public:
    Const(string val):Expression(val){}
    Expression* copy(){
        return new Const(ope);
    }
    Expression* derivation(){
        return new Const("0");
    }
};
class Varible: public Expression{
public:
    Varible():Expression("x"){}
    Expression *copy(){
        return new Varible();
    }
    Expression* derivation(){
        return new Const("1");
    }
};
class Sum: public Expression{
public:
    Sum(Expression* left, Expression* right):Expression("+",left, right){}
	Expression* derivation();
    Expression *copy(){
        return new Sum(lopd->copy(), ropd->copy());
    }
};
Sum* operator+(Expression &a, Expression &b){
    return new Sum(&a, &b);
}
Expression* Sum::derivation(){
	Expression &du=*(lopd->derivation()), &dv=*(ropd->derivation()); 
	return du+dv;
}
class Difference: public Expression{
public:
    Difference(Expression* left, Expression* right):Expression("-", left, right){}
    Expression *copy(){
        return new Difference(lopd->copy(), ropd->copy());
    }
	Expression* derivation();
};
Difference* operator-(Expression &a, Expression &b){
    return new Difference(&a, &b);
}
Expression* Difference::derivation(){
	Expression &du=*(lopd->derivation()), &dv=*(ropd->derivation()); 
	return du-dv;
}
class Product: public Expression{
public:
    Product(Expression* left, Expression* right):Expression("*", left, right){}
    Expression *copy(){
        return new Product(lopd->copy(), ropd->copy());
    }
    Expression* derivation();
};
Product* operator*(Expression &a, Expression &b){
    return new Product(&a, &b);
}
Expression* Product::derivation(){
	Expression &u=*(lopd->copy()), &v=*(ropd->copy());
	Expression &du=*(u.derivation()), &dv=*(v.derivation());
	return *(du*v)+*(u*dv);
}
class Power2: public Expression{
public:
    Power2(Expression *left): Expression("^", left, new Const("2")){}
    Expression *copy(){
        return new Power2(lopd->copy());
    }
    Expression* derivation(){return NULL;}
};
class Quotient: public Expression{
public:
    Quotient(Expression* left, Expression* right): Expression("/", left, right){}
    Expression *copy(){
        return new Quotient(lopd->copy(), ropd->copy());
    }
    Expression* derivation();
};
Quotient* operator/(Expression &a, Expression &b){
    return new Quotient(&a, &b);
}
Expression* Quotient::derivation(){
	Expression &u=*(lopd->copy()), &v=*(ropd->copy());
	Expression &du=*(u.derivation()), &dv=*(v.derivation());
	return *(*(du*v)-*(u*dv))/(*(new Power2(v.copy())));
}
class Minus: public Expression{
public:
    Minus(Expression *right): Expression("_", NULL, right){}
    Expression *copy(){
        return new Minus(ropd->copy());
    }
    Expression *derivation();
};
Minus* operator-(Expression &a){
    return new Minus(&a);
}
Expression* Minus::derivation() {
    if(ropd->ope[0] == 'x')
        return new Const("-1");
    if(isdigit(ropd->ope[0]))
        return new Const("0");
    Expression &re=*(ropd->derivation());
    return -re;
}
class Ln: public Expression{
public:
    Ln(Expression *right): Expression("ln", NULL, right){}
    Expression *copy(){
        return new Ln(ropd->copy());
    }
    Expression *derivation();
};
Ln* ln(Expression *b){
    return new Ln(b);
}
Expression* Ln::derivation(){
	Expression &v=*(ropd->copy()), &dv=*(ropd->derivation());
	return dv/v;
}
Expression *toExpression(const string &s){
    size_t i=0, n=s.length();
    stack<Expression*> operands;
    stack<string> oper;
    oper.push("@");
    while (i<n) {
        string item;
        if(isdigit(s[i])||s[i]=='.'){//读取数值常量
            while(s[i]=='.'||isdigit(s[i]))
                item+=s[i++];
            operands.push(new Const(item));
            continue;
        }
        if(s[i]=='x'){//读取变量x
            item+=s[i++];
            operands.push(new Varible());
            continue;
        }
        if(s[i]=='('){//读取左括弧
            item+=s[i++];
            oper.push(item);
            continue;
        }
        item+=s[i++];//读取运算符
        if(item=="l")item+=s[i++];//是对数运算
        string t=oper.top();
        while (priority[t]>1&&(priority[item]<=priority[t])) {
            oper.pop();
            Expression *l=NULL, *r=operands.top();
            operands.pop();
            if(t!="ln"&&t!="_"){//t是二元运算符
                l=operands.top();
                operands.pop();
            }
            Expression* e;
            switch (priority[t]) {
                case 3:
                    if(t=="+") e=(*l)+(*r);
                    else e=(*l)-(*r);
                    break;
                case 4:
                    if(t=="*")e=(*l)*(*r);
                    else e=(*l)/(*r);
                    break;
                case 5:
                    e=ln(r);
                    break;
                default:
                    e=-(*r);
                    break;
            }
            operands.push(e);
            t=oper.top();
        }
        if(item==")")
            oper.pop();
        else
            oper.push(item);
    }
    return operands.top();
}
void symbleDerivation(string &s){
	preprocess(s);
	Expression* exp=toExpression(s);
	Expression* deriv=exp->derivation();
	delete exp;
	s="";
	deriv->toString(s);
    delete deriv;
	fix(s);
}
int main(){
    ifstream inputdata("Symbolic Derivation/inputdata.txt");
    ofstream outputdata("Symbolic Derivation/outputdata.txt");
    string s;
    while (inputdata>>s) {
	symbleDerivation(s);
        outputdata<<s<<endl;
        cout<<s<<endl;
    }
    inputdata.close();
	outputdata.close();
	return 0;
} 