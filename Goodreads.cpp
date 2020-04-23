#include "Goodreads.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>



#define NUMBER_OF_THREADS 4
pthread_mutex_t mutex_books;
pthread_mutex_t mutex_books1;

using namespace std;

typedef struct tdata
{
    long tid;
    Goodreads* gr;
    const char* genre;
}TData;




vector <string> split(string s, char delim) {
    vector <string> splited;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delim)){
        splited.push_back(token);
    }
    return splited;
}

void Goodreads::parse_book_file (string filename, string genre) {

    fstream fs;
    string line;
    vector<string> book_data;
    fs.open(filename);
 
    while (getline(fs, line))
    {
        book_data = split(line, ',');
        if (book_data[GENRE_1] == genre || book_data[GENRE_2] == genre)
            books.insert(pair<int, Book> (stoi(book_data[BOOK_ID]), Book(book_data)));
    }
}


void Goodreads::add_reviews(string file) {
    fstream fs;
    string line;
    fs.open(file);
    getline(fs, line);
    auto columns_name = split(line, ',');
    int count = 0;
    const clock_t start = clock();

    while (getline(fs, line))
    {
        auto review = split(line, ',');
        if (books.find(stoi(review[0])) != books.end())
            books[stoi(review[0])].add_review(stoi(review[1]), stoi(review[2]));
        
        count++;
    }
    const clock_t add_end = clock();
    cout << "Single Thread Add Review Time" << float(add_end - start) / CLOCKS_PER_SEC << endl;

}


Book Goodreads::find_fav_book(string genre) {
    vector<pthread_t> threads(NUMBER_OF_THREADS);
    vector<TData> tds(NUMBER_OF_THREADS);

    const clock_t begin_time = clock();

    parse_book_file(string(DIR).append(BOOKS_FILE), genre);
    const clock_t parse_end = clock();
    cout << float(parse_end - begin_time) / CLOCKS_PER_SEC << endl;

    for (long i = 0; i < NUMBER_OF_THREADS; i++) {
        tds[i].genre = genre.c_str();
        tds[i].gr = this;
        tds[i].tid = i;
        pthread_create(&threads[i], NULL, add_reviews_, (void*)&tds[i]);
    }
        for (long i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    // add_reviews(string(DIR).append(REVIEWS_FILE));
    const clock_t add_end = clock();
    cout << float(add_end - parse_end) / CLOCKS_PER_SEC << endl;
    
    auto fav_book = max_element(books.begin(), books.end(), 
    [](const pair<int, Book>& b1, const pair<int, Book>& b2) {
        return b1.second.rate() < b2.second.rate(); });

    return fav_book->second;
}


void* Goodreads::add_reviews_(void* arg) {

    fstream fs;
    string line;
    auto td = (TData*)arg;
    auto gr = td->gr;

    map <int, int[2]> reviews;
    string filename = string(DIR) + "reviews_" + to_string(td->tid) + ".csv";
    fs.open(filename);
    getline(fs, line);
    auto columns_name = split(line, ',');
    const clock_t start = clock();
    int count = 0;
    while (getline(fs, line))
    {
        auto review = split(line, ',');
        if (gr->books.find(stoi(review[0])) != gr->books.end()) {
            reviews[stoi(review[0])][0] += (stoi(review[1]) * stoi(review[2]));
            reviews[stoi(review[0])][1] += stoi(review[2]); 
        }
        count++;
    }
    fs.close();
    const clock_t end = clock();
    for (auto it = reviews.begin(); it != reviews.end(); it++ )
    {
        pthread_mutex_lock(&mutex_books);
        gr->books[it->first].add_review(it->second[0], it->second[1]);
        pthread_mutex_unlock(&mutex_books);
    }
    const clock_t end_end = clock();
    string res;
    res = to_string(float(end - start) / CLOCKS_PER_SEC) +
         "-" + 
         to_string(float(end_end - end) / CLOCKS_PER_SEC) +
          "-" + to_string(count) +"\n";
    cout << res ;

}