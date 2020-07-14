#pragma once
#include<vector>
#include<map>
#include<queue>
#include<string>
#include<sstream>
#include<fstream>
#include<regex>
#include<algorithm>
#include<climits>

using namespace std;


struct pin
{
	
	int x;
	int y;
	int layer;
	string id;
	/*
	pin(int x_, int y_ ,int z_, string id_)
	{
		x=x_;
		y=y;
		layer=z_;
		id=id_;
	}*/
};

struct cell {
	int x;
	int y;
	int layer;
	int f;
	char pre;
	string id;
	cell(pin p) {
		x = p.x;
		y = p.y;
		layer = p.layer;
		id = p.id;
		f = 0;
	}
	cell() {
		x = 0;
		y = 0;
		layer = 0;
		f = 0;
		pre = '\0';
		id = "";
	}/*
	cell& operator=(const cell& a)
	{
		x = a.x;
		y = a.y;
		layer = a.layer;
		f = a.f;
		pre = a.pre;
		id = a.id;
		return *this;
	}*/
	bool operator==(const cell& a) const
	{
		return (x == a.x && y == a.y && layer == a.layer);
	}
	bool operator!=(const cell& a) const
	{
		return (x != a.x || y != a.y || layer != a.layer);
	}
};

struct myCompare {
	bool operator()(cell c1, cell c2)
	{
		return c1.f < c2.f;
	}
};


typedef std::priority_queue<cell, vector<cell>, myCompare> mypq_type;



struct net{
	vector<pin> pins;
	vector<pin> paths;
	int boxsize;
};

typedef vector<net> netList;
typedef vector<vector<vector<cell> > > cellGrid;
typedef vector<vector<vector<int> > > visGrid;
