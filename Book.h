#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <map>


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
    float rate() const;
    // inline bool operator< (const Book& l, const Book& r){return r.rate() < l.rate() }
    // inline bool operator> (const Book& l, const Book& r){ return  r.rate() < l.rate(); }
    friend std::ostream& operator<<(std::ostream& os, const Book& bk);
};


#endif