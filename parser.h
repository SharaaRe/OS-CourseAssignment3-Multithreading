#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

typedef std::vector<std::string> Book;
typedef std::vector<std::string> Review;


std::vector <std::string> split(std::string s, char delim);
std::vector <std::vector<std::string>> parse_csv(std::string filename);

#endif
