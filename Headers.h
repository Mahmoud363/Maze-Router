#pragma once
#include<vector>
#include<map>
#include<queue>
#include<string>
#include<sstream>
#include<fstream>
#include<regex>
#include<algorithm>


using namespace std;


struct pin
{
	int x;
	int y;
	int layer;
	string id;
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
	}
	cell() {
		x = 0;
		y = 0;
		layer = 0;
		f = 0;
		pre = '\0';
		id = "";
	}
};

struct myCompare {
	bool operator()(cell const& c1, cell const& c2)
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
