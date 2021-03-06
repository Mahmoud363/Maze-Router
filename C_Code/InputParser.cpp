#include "InputParser.h"
#include <string>
#include <climits>
void InputParser::computeNetsArea(){
	
	for (int i = 0; i < NetList.size(); i++) {
		int mini = 99999999, maxi = -1, minj = 99999999, maxj = -1, mink = 99999999, maxk = -1;
		for (int j = 0; j < NetList[i].pins.size(); j++) {
			mini = min(mini, NetList[i].pins[j].x);
			minj = min(minj, NetList[i].pins[j].y);
			mink = min(mink, NetList[i].pins[j].layer);
			maxi = max(maxi, NetList[i].pins[j].x);
			maxj = max(maxj, NetList[i].pins[j].y);
			maxk = max(maxk, NetList[i].pins[j].layer);
		}
		NetList[i].boxsize = (maxi - mini + 1) * (maxj - minj + 1)/**(maxk-mink+1)*/;
	}
}
int InputParser::getMaxLayer() {
	return maxLayer;
}
bool comp(net& a, net& b)
{
	return a.boxsize < b.boxsize;
}

void InputParser::sortNets()
{
	sort(NetList.begin(), NetList.end(), comp);
}
InputParser::InputParser(string sourcePath)
{
	ifstream read(sourcePath);

	// Template instantiations for 
	// extracting the matching pattern. 

	string line;
	int counter = 1;
	//getline(read, line);
	while (!read.eof()) {
		getline(read, line);
		smatch match;
		regex r("\\((.*?)\\)");
		string subject = line;
		int j = 0;

		net Net;
		while (regex_search(subject, match, r)) {

			j++;
			//Extracting the details for each pin without the brackets
			string parse = match.str(0).substr(1, match.str(0).size() - 2);
			//Entering the details of the pin into the struct pin
			stringstream ss(parse);
			struct pin newpin;
			for (int i = 0; i < 3; i++) {
				string substr;
				getline(ss, substr, ',');
				switch (i) {
				case 0:
					newpin.layer = atoi(substr.c_str()) - 1;
				case 1:
					newpin.x = atoi(substr.c_str()) - 1;
				case 2:
					newpin.y = atoi(substr.c_str()) - 1;
				}
			}
			maxLayer = max(maxLayer, newpin.layer + 1);
			newpin.id= "n"+to_string(counter)+"_p"+to_string(j);
			cout << newpin.layer << "/" << newpin.x << "/" << newpin.y << "/" << newpin.id << endl;
			Net.pins.push_back(newpin);
			cell c(newpin);
			// suffix to find the rest of the string. 
			subject = match.suffix().str();

		}
		NetList.push_back(Net);
		counter++;
	}

}

InputParser::~InputParser()
{
}



netList  InputParser::getNetList() {
	return NetList;
}


int main ()
{

	string str;
	cin >> str;
	InputParser inp(str);
	netList n = inp.getNetList();

	int i = 0;

}
