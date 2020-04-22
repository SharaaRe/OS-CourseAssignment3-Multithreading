#include "parser.h"

#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>

#include "Book.h"

#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"
#define DIR "./datasets/"

using namespace std;

inline float rate(float author_rate, int rate_sum, int number_of_likes) {
    return (author_rate + (rate_sum / number_of_likes)) / 10;
}


Book find_favorite_book(string genre){
    auto books = parse_books_csv(string(DIR).append(BOOKS_FILE), genre);
    add_reviews(string(DIR).append(REVIEWS_FILE), books);

    auto fav_book = max_element(books.begin(), books.end(), 
    [](const pair<int, Book>& p1, const pair<int, Book>& p2) {
        return p1.second.rate() < p2.second.rate(); });

    return fav_book->second;
}


int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << "Few Arguments for Program!" << endl;
        exit(EXIT_FAILURE);
    } 

    string genre(argv[1]);
    cout << find_favorite_book(genre);
    return 0;

}