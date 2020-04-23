#include <iostream>
#include <string>
#include <ctime>

#include "Goodreads.h"

using namespace std;


int main(int argc, char* argv[])
{
    const clock_t begin_time = clock();

    if (argc < 2){
        cerr << "Few Arguments for Program!" << endl;
        exit(EXIT_FAILURE);
    } 
    string genre(argv[1]);
    cout << Goodreads().find_fav_book(genre);

    cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    return 0;

}