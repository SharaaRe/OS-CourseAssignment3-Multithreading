#include "parser.h"
#include "Book.h"

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

map<int, Book> parse_books_csv(string filename, string genre) {
    fstream fs;
    string line;
    vector <vector <string>> file_data;
    map <int, Book> books;
    vector<string> book_data;
    fs.open(filename);
 
    while (getline(fs, line))
    {
        book_data = split(line, ',');
        if (book_data[GENRE_1] == genre || book_data[GENRE_2] == genre)
            books.insert(pair<int, Book> (stoi(book_data[BOOK_ID]), Book(book_data)));
    }

    return books;
}


void add_reviews(string file, std::map<int, Book>& books) {
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
