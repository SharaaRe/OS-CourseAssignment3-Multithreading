#include "parser.h"


using namespace std;


vector <string> split(string s, char delim) {
    vector <string> splited;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delim)){
        // token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        splited.push_back(token);
    }
    // for (int i = 0; i < splited.size(); i++)
    //     cout << splited[i] << "    ";
    // cout << endl;
    return splited;
}

vector <vector<string>> parse_csv(string filename) {
    fstream fs;
    string line;
    vector <vector <string>> file_data;
    fs.open(filename);
    while (getline(fs, line))
    {
        file_data.push_back(split(line, ','));
    }

    return file_data;
}
