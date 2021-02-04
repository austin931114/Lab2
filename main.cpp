#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <list>
using namespace std;


int checkCapital(string str) { 
	int indicator = 0;
    // Traverse the string 
		if (str != "I") {
			for(int i=0; i < 1; i++) { 
					if (str[i]>='A' && str[i]<='Z') { 
						indicator = 1;
						break;
					} 
			} 
		}
		return indicator;
} 

int main(int argc, char *argv[]) {
  vector<string> tokens;
	set <string> unique;
	string next_line;  // Each data line
	string filename = argv[1];
	ifstream in(filename);
	while (getline(in, next_line)) {
			istringstream iss(next_line);
			string token;
			while (iss >> token) {
					string nopunct = "";
					for(auto &c : token) { // Remove Punctuation      
							if (isalpha(c)) {  // c = one of the char in token(string)
									nopunct +=c;       
							}
					}

					for (int i = 1; i < token.length(); i++) {
        		if (isupper(token[i])) {
							token[i] = token[i] + 32;
							token.insert(i, " ");
						}

					}
					tokens.push_back(nopunct);
					unique.insert(nopunct);
			// cout << token<<endl;
		}
	}
	cout << "Number of words "<<tokens.size()<<endl;
	cout << "Number of unique words "<<unique.size()<<endl;
	ofstream setfile(filename + "_set.txt");
	for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {
			// cout << ' ' << *it;
			setfile << ' ' << *it;
	}
	cout << endl;

	map<string, string> wordmap;
	string last="";
	ofstream setMapFile(filename + "_map.txt");
	for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
			wordmap[last]=*it; // last = key, *it = value
			last = *it;
	}
	for (map<string, string>::iterator it=wordmap.begin(); it!=wordmap.end(); ++it) {
			// ++it moves 'it' to the next value in the container
			// cout << it->first<<", " << it->second<<endl;
			setMapFile << it->first<< ", " << it->second<<endl;
	}

	string state = "";
	for(int i = 0; i < 100; i++){
		// cout << wordmap[state] << " ";
		state = wordmap[state];
	}
	cout << endl;

	map<string, vector<string>> createText;
	state = "";
	for(vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
		createText[state].push_back(*it);
		// state = key, push_back(*it) = push 'value' to vector
		state = *it;
  }

	for(vector<string>::iterator it=createText["Nephi"].begin(); it!=createText["Nephi"].end(); it++) { // search every value in 'vector' that has key 'Nephi', so 
							// only need to loop 'vector' dont need 'map'
		// cout << *it << ", ";
	}

	srand(time(NULL)); // this line initializes the random number generated
										// so you dont get the same thing every time
	state = "";
	for (int i = 0; i < 100; i++) {
		int ind = rand() % createText[state].size();
		// cout << createText[state][ind] << " ";
		// ind = get a random word from the 'key'
		state = createText[state][ind];

	}
	cout << endl;

	map<list<string>, vector<string>> finalText;
  list<string> textState;
  for (int i = 0; i < 4; i++) {
    textState.push_back("");
  }
                        
  for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
    finalText[textState].push_back(*it);
    textState.push_back(*it);
    textState.pop_front();
  }
	
	textState.clear();
  for (int i = 0; i < 4; i++) {
    textState.push_back("");
  }
  for (int i = 0; i < 150; i++) {
    int ind = rand() % finalText[textState].size();
		int capital = 0;
		capital = checkCapital(finalText[textState][ind]);
		if (i != 0 & capital == 1) {
			cout << ".";
		}
    cout << " " << finalText[textState][ind];
    textState.push_back(finalText[textState][ind]);
    textState.pop_front();
  }
	cout  << "." << endl;
}
