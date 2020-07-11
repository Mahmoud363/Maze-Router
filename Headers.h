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
};

typedef vector<net> netList;

