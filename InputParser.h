#pragma once
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Headers.h"
using namespace std;


/*netList NetList;
string sourcePath;
int maxLayer=-1;
vector<vector<vector<int> > > vec(5, vector<vector<int> >(3, vector <int>(2, 4)));
*/

class InputParser
{
public:
	InputParser(string sourcePath);
	netList getNetList();
	int getMaxLayer();
	~InputParser();

private:
	string line;
	netList NetList;
	int maxLayer = -1;
};

