#include <iostream>
#include <string>
#include <ctime>

#include "Goodreads.h"

using namespace std;


int main(int argc, char* argv[])
{

    if (argc < 2){
        cerr << "Few Arguments for Program!" << endl;
        exit(EXIT_FAILURE);
    } 
    string genre(argv[1]);
    Book b = Goodreads().find_fav_book_serie(genre);
    cout << b;


    return 0;

}