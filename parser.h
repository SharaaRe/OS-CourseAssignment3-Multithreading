#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

#include "Book.h"

enum indexes{BOOK_ID, BOOK_TITLE, GENRE_1, GENRE_2, PAGES, AUTHOR_NAME, AUTHOR_AVERAGE_RATING};
// 
// typedef std::vector<std::string> Book;
// typedef std::vector<std::string> Review;


std::vector <std::string> split(std::string s, char delim);
std::vector <std::vector<std::string>> parse_csv(std::string filename);
std::map<int, Book> parse_books_csv(std::string filename, std::string genre);
void add_reviews(std::string file, std::map<int, Book>&);


#endif
