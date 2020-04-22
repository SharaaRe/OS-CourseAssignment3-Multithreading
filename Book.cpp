#include "Book.h"
#include "parser.h"

#include <iostream>

using namespace std;
Book::Book(vector<string> fields) {
    id = stoi(fields[BOOK_ID]);
    title = fields[BOOK_TITLE];
    genre_1 = fields[GENRE_1];
    genre_2 = fields[GENRE_2];
    pages = stoi(fields[PAGES]);
    author = fields[AUTHOR_NAME];
    author_average_rating = stof(fields[AUTHOR_AVERAGE_RATING]);
}

void Book::add_review(int rate, int num) {
    reviews_sum += rate * num;
    reviews_likes_count += num;
}

float Book::rate(){
    return (author_average_rating + (reviews_sum / reviews_likes_count)) / 10;
}

ostream& operator<<(ostream& os, const Book& bk) {
    os << "id: " << bk.id << endl;
    os << "Title: " << bk.title << endl;
    os << "Genres: " << bk.genre_1 << ", " << bk.genre_2 << endl;
    os << "Number of Pages: " << bk.pages << endl;
    os << "Author: " << bk.author << endl;
    os << "Author Rating: " << bk.author_average_rating << endl;

    return os;
    

}
