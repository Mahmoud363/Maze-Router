#include "InputParser.h"
int InputParser::getMaxLayer() {
	return maxLayer;
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
			pin newpin;
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
			cout << newpin.layer << "/" << newpin.x << "/" << newpin.y << "/" << newpin.id << endl;
			Net.pins.push_back(newpin);

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

/*
int main ()
{

	string str;
	cin >> str;
	InputParser inp(str);
	netList n = inp.getNetList();

	int i = 0;

}
*/