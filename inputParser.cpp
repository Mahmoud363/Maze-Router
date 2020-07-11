#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
using namespace std;

struct pin
{
	int layer;
	int x;
	int y;
	string id;
};

string strip_spaces(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

vector<string> split_commas(string str) {
	str += ',';
	vector<string> buffer;
	string tmp;
	while (!str.empty()) {
		tmp = str.substr(str.find(',')+1);
		buffer.push_back(tmp);
		str.erase(str.begin(), str.end() + (str.find(','));
	}
	return buffer;
}

int main()
{
	vector<vector<string>> parsedNet;
	string sourcePath;
	cin >> sourcePath;

	ifstream read(sourcePath);



	// Template instantiations for 
	// extracting the matching pattern. 
	int netCounter = 1;

	string line;
	getline(read, line);
	while (!read.eof()) {
		vector<string> net;
		vector<string> pinValues;
		smatch match;
		regex r("\\((.*?)\\)");
		string subject = line;
		int i = 1;
		while (regex_search(subject, match, r)) {
			cout << "\nMatched string is " << match.str(0) << endl
				<< "and it is found at position "
				<< match.position(0) << endl;
			i++;
			string parse = match.str(0).substr(1, match.str(0).size()-2);
			parse = strip_spaces(parse);
			pinValues = split_commas(parse);


			// suffix to find the rest of the string. 
			subject = match.suffix().str();
		}
		getline(read, line);
	}

	return 0;
}
