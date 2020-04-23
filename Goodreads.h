#ifndef GOODREADS_H
#define GOODREADS_H

#include <map>

#include "Book.h"


#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"
#define DIR "./datasets/"

class Goodreads {
private:
    std::map <int, Book> books;
    void parse_book_file(std::string filename, std::string genre);
    void add_reviews(std::string filename);

public:
    static void* parse_book_(void*);
    static void* add_reviews_(void*);
    Book find_fav_book_serie(std::string genre);
    Book find_fav_book_parallel(std::string genre);

};

#endif