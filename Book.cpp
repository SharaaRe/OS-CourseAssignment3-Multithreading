#include "Book.h"
#include "parser.h"
using namespace std;
Book::Book(vector<string> fields) {
    id = stoi(fields[BOOK_ID]);
    title = fields[BOOK_TITLE];
    genre_1 = fields[GENRE_1];
    genre_2 = fields[GENRE_2];
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