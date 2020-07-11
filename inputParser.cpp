#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
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
			//Extracting the details for each pin without the brackets
			string parse = match.str(0).substr(1, match.str(0).size()-2);
			//Entering the details of the pin into the struct pin
			stringstream ss(parse); 
			pin newpin;
			for(int i=0;i<3;i++) { 
				string substr; 
				getline(ss, substr, ',' ); 
				switch(i){
					case 0:
						newpin.layer= atoi(substr.c_str());
					case 1:
						newpin.x= atoi(substr.c_str());
					case 2:
						newpin.y= atoi(substr.c_str());
				}
			} 

			cout<< newpin.layer<<"/"<<newpin.x<<"/"<<newpin.y<<endl;

			// suffix to find the rest of the string. 
			subject = match.suffix().str();
		}
		getline(read, line);
	}

	return 0;
}
