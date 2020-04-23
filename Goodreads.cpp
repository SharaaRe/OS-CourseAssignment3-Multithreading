#include "Goodreads.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>



#define NUMBER_OF_THREADS

using namespace std;



vector <string> split(string s, char delim) {
    vector <string> splited;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delim)){
        splited.push_back(token);
    }
    return splited;
}

void Goodreads::parse_book_file (string filename, string genre) {

    fstream fs;
    string line;
    vector<string> book_data;
    fs.open(filename);
 
    while (getline(fs, line))
    {
        book_data = split(line, ',');
        if (book_data[GENRE_1] == genre || book_data[GENRE_2] == genre)
            books.insert(pair<int, Book> (stoi(book_data[BOOK_ID]), Book(book_data)));
    }
}


void Goodreads::add_reviews(string file) {
    fstream fs;
    string line;
    fs.open(file);
    getline(fs, line);
    auto columns_name = split(line, ',');
    while (getline(fs, line))
    {
        auto review = split(line, ',');
        if (books.find(stoi(review[0])) != books.end())
            books[stoi(review[0])].add_review(stoi(review[1]), stoi(review[2]));
    }
}


Book Goodreads::find_fav_book(string genre) {
    parse_book_file(string(DIR).append(BOOKS_FILE), genre);
    add_reviews(string(DIR).append(REVIEWS_FILE));

    auto fav_book = max_element(books.begin(), books.end(), 
    [](const pair<int, Book>& b1, const pair<int, Book>& b2) {
        return b1.second.rate() < b2.second.rate(); });

    return fav_book->second;
}