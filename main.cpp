#include <iostream>
#include <string>

#include "Goodreads.h"



using namespace std;


int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << "Few Arguments for Program!" << endl;
        exit(EXIT_FAILURE);
    } 

    string genre(argv[1]);
    cout << Goodreads().find_fav_book(genre);
    // cout << "ehem";

    return 0;

}