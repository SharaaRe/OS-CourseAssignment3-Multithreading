#include "Book.h"
#include <iostream>

using namespace std;


int main() {
    vector <string> fields;
    fields.push_back("456");
    fields.push_back("T1");
    fields.push_back("g1");
    fields.push_back("g2");
    fields.push_back("950");
    fields.push_back("auth1");
    fields.push_back("3.265645");

    Book book(fields);
    cout << book << endl;


}