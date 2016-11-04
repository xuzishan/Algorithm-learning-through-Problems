//
//  maxflow.h
//  laboratory
//
//  Created by Ðì×ÓÉº on 15/6/15.
//  Copyright (c) 2015Äê xu_zishan. All rights reserved.
//
#ifndef _MAXFLOW_H
#define _MAXFLOW_H
#include <queue>
#include "Graph.h"
class Network: public Graph<int>{
private:
    vector<Color> color;
    vector<int> d;
    vector<int> pi;
    void reset();
	void bfsVisit(int s);
public:
    Network(int n);
    friend int maxFlow(Network &G, vector<vector<int>> &c, int s, int t);
};
#endif /*_MAXFLOW_H*/