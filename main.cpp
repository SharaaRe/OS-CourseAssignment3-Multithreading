#include "parser.h"

#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>

#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"
#define DIR "./datasets/"

using namespace std;

inline float rate(float author_rate, int rate_sum, int number_of_likes) {
    return (author_rate + (rate_sum / number_of_likes)) / 10;
}


Book find_best_book(string genre) {
    Book best_book;
    float best_rate = 0;
    vector <Book> books = parse_csv(string(DIR).append(BOOKS_FILE));
    map <string, int> book_data_ind;
    for (int i = 0; i < books[0].size(); i++) {
        book_data_ind.insert(pair <string, int> (books[0][i], i));
    }
    vector <Review> raw_reviews = parse_csv(string(DIR).append(REVIEWS_FILE));
    map <int, pair<int, int>> reviews;
    for (int i = 1; i < raw_reviews.size(); i++){
        cout << "Eheeeem" << i << raw_reviews[i][0] << "-" << raw_reviews[i][1] << endl;
        if (reviews.find(stoi(raw_reviews[i][0])) == reviews.end()) {
            reviews[stoi(raw_reviews[i][0])] =
                     pair<int, int> (stoi(raw_reviews[i][1]), stoi(raw_reviews[i][2]));
        } else {

            reviews[stoi(raw_reviews[i][0])].first += (stoi(raw_reviews[i][1]) *  stoi(raw_reviews[i][2]));
            reviews[stoi(raw_reviews[i][0])].second += stoi(raw_reviews[i][2]);
        }
    }


    for (int i = 0; i < books.size(); i++){
        float book_rate;
        if (books[i][book_data_ind["genre_1"]] == genre or
                books[i][book_data_ind["genre_2"]] == genre) {
            auto review = reviews[stoi(books[i][book_data_ind["book_id"]])];

            if ((book_rate = rate(stof(books[i][book_data_ind["author_average_rating"]]),
                     review.first, review.second)) > best_rate) {
                best_rate = book_rate;
                best_book = books[i];
            }
        }
    }
    
    return best_book;

}


int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << "Few Arguments for Program!" << endl;
        exit(EXIT_FAILURE);
    } 

    string genre(argv[1]);
    Book book = find_best_book(genre);
    for (int i = 0; i < book.size(); i++) {
        cout << book[i] << endl;
    }

}