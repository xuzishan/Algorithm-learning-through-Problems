//
//  Graph.h
//  laboratory
//
//  Created by 徐子珊 on 15/6/15.
//  Copyright (c) 2015年 xu_zishan. All rights reserved.
//
#ifndef _GRAPH_H
#define _GRAPH_H
	#include <vector>
	#include <list>
	#include <algorithm>
	using namespace std;
	enum Color{WHITE, GRAY, BLACK};
	template<typename T>
	class Graph{
	protected:
		vector<list<T>> A;
		int scale;
	public:
		Graph(int n):scale(n),A(n, list<T>()){}
		Graph(Graph &G);
		list<T> getList(int v){return A[v];}
		int size(){return scale;}
		void insertEdge(int u, T v);
		void deleteEdge(int u, T v);
	};
	template<typename T>
	Graph<T>::Graph(Graph<T> &G){
		scale=G.scale;
		A=vector<list<T>>();
		for (int u=0; u<G.scale; u++)
			A.push_back(list<T>(G.A[u]));
	}
	template<typename T>
	void Graph<T>::insertEdge(int u, T v){
		A[u].push_back(T(v));
	}
	template<typename T>
	void Graph<T>::deleteEdge(int u, T v){
		list<T>::iterator i=find(A[u].begin(), A[u].end(), v);
		A[u].erase(i);
	}
#endif /*_GRAPH_H*/