#include "Goodreads.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>



#define NUMBER_OF_THREADS 8
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

    while (getline(fs, line))
    {
        auto review = split(line, ',');
        if (books.find(stoi(review[0])) != books.end())
            books[stoi(review[0])].add_review(stoi(review[1]), stoi(review[2]));
        
        count++;
    }

}


Book Goodreads::find_fav_book_parallel(string genre) {

    vector<pthread_t> threads(NUMBER_OF_THREADS);
    vector<TData> tds(NUMBER_OF_THREADS);
    parse_book_file(string(DIR).append(BOOKS_FILE), genre);
    
    // start of parallel implementation
    for (long i = 0; i < NUMBER_OF_THREADS; i++) {
        tds[i].genre = genre.c_str();
        tds[i].gr = this;
        tds[i].tid = i;
        pthread_create(&threads[i], NULL, reviews_job, (void*)&tds[i]);
    }
        for (long i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    // end of parallel implementation

    auto fav_book = max_element(books.begin(), books.end(), 
    [](const pair<int, Book>& b1, const pair<int, Book>& b2) {
        return b1.second.rate() < b2.second.rate(); });

    return fav_book->second;
}

Book Goodreads::find_fav_book_serie(string genre) {

    parse_book_file(string(DIR).append(BOOKS_FILE), genre);
    add_reviews(string(DIR).append(REVIEWS_FILE));

    auto fav_book = max_element(books.begin(), books.end(), 
    [](const pair<int, Book>& b1, const pair<int, Book>& b2) {
        return b1.second.rate() < b2.second.rate(); });

    return fav_book->second;
}


void* Goodreads::reviews_job(void* arg) {
 
    auto td = (TData*)arg;
    auto gr = td->gr;

    map<int, int[2]> reviews;
    gr->read_reviews(td->tid, reviews);
    gr->add_reviews_sum(reviews);

}

void Goodreads::read_reviews(int partition, map<int, int[2]>& reviews) {

    int start, end, length, count = 0;
    fstream fs;
    string line;
    fs.open(string(DIR) + REVIEWS_FILE,
             fstream::in | fstream::out);

    fs.seekg (0, fs.end);
    length = fs.tellg();
    fs.seekg (0, fs.beg);
    start = length / NUMBER_OF_THREADS * partition;
    end = partition == NUMBER_OF_THREADS - 1? length 
            : length / NUMBER_OF_THREADS * (partition + 1);
    fs.seekg(start);
    getline(fs, line);

    while (getline(fs, line)) {
        auto review = split(line, ',');
        if (books.find(stoi(review[0])) != books.end()) {

            reviews[stoi(review[0])][0] += (stoi(review[1]) * stoi(review[2]));
            reviews[stoi(review[0])][1] += stoi(review[2]); 
        }

        count++;

        if (fs.tellg() > end)
            break;
    }

    fs.close();
}

void Goodreads::add_reviews_sum(std::map<int, int[2]>& reviews) {
   
    for (auto it = reviews.begin(); it != reviews.end(); it++ )
    {
        pthread_mutex_lock(&mutex_books);
        books[it->first].add_reviews_by_group(it->second[0], it->second[1]);
        pthread_mutex_unlock(&mutex_books);
    }
}