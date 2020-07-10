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

int main()
{
	string subject("n1 (1, 10, 20) (2, 30, 50) (1, 5 ,1000) "
		"n2 (1, 10, 20) (2, 30, 50) (1, 5 ,1000)");

	vector<vector<string>> parsedNet;
	string sourcePath;
	cin >> sourcePath;

	ifstream read(sourcePath);



	// Template instantiations for 
	// extracting the matching pattern. 
	
	string line;
	getline(read, line);
	while (!read.eof()) {
		smatch match;
		regex r("\\((.*?)\\)");
		string subject = line;
		int i = 1;
		while (regex_search(subject, match, r)) {
			cout << "\nMatched string is " << match.str(0) << endl
				<< "and it is found at position "
				<< match.position(0) << endl;
			i++;
			string parse = match.str(0);


			// suffix to find the rest of the string. 
			subject = match.suffix().str();
		}
		getline(read, line);
	}

	return 0;
}
