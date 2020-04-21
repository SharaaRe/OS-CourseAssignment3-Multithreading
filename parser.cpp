#include "parser.h"


using namespace std;


vector <string> split(string s, char delim) {
    vector <string> splited;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delim)){
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        splited.push_back(token);
    }
    return splited;
}

vector <vector<string>>* parse_csv(string filename) {
    fstream fs;
    string line;
    vector <vector <string>>* file_data = new vector<vector<string>>;
    fs.open(filename);
    while (getline(fs, line))
    {
        file_data->push_back(split(line, ','));
    }
    return file_data;
}
