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
    void *hello();
    static void* hello_helper(void* gr);
    Book find_fav_book(std::string genre);
};

#endif