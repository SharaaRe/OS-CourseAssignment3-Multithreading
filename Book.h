#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <map>

enum indexes{BOOK_ID, BOOK_TITLE, GENRE_1, GENRE_2, PAGES, AUTHOR_NAME, AUTHOR_AVERAGE_RATING};


class Book
{
protected:
    int id;
    std::string title;
    std::string genre_1;
    std::string genre_2;
    int pages;
    std::string author;
    float author_average_rating;
    int reviews_sum;
    int reviews_likes_count;


public:
    Book() = default;
    Book(std::map<std::string, std::string> fields);
    Book(std::vector<std::string> fields);
    void add_review(int rate, int number_of_likes);
    inline float rate() const;
    friend std::ostream& operator<<(std::ostream& os, const Book& bk);
};


inline float Book::rate() const{
    return (author_average_rating + ((float)reviews_sum / reviews_likes_count)) / 10;
}


#endif