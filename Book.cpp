#include "Book.h"

#include <iostream>
#include <iomanip>

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
    // pthread_mutex_lock(&mutex);
    reviews_sum += rate * num;
    reviews_likes_count += num;
    // pthread_mutex_unlock(&mutex);

}


ostream& operator<<(ostream& os, const Book& bk) {
    os << fixed << setprecision( 2 );
    os << "id: " << bk.id << endl;
    os << "Title: " << bk.title << endl;
    os << "Genres: " << bk.genre_1 << ", " << bk.genre_2 << endl;
    os << "Number of Pages: " << bk.pages << endl;
    os << "Author: " << bk.author << endl;
    os << "Author Rating: " << bk.author_average_rating << endl;

    return os;
    

}
