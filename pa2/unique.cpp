/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Jason Qiu
 * Date        : October 01, 2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int l = s.length();
    for(int i = 0; i < l; i++){
        if(!(std::islower(s[i]))){
            // islower also returns false on non-alphabetic characters with the default C locale, like '坏' or '0' or '$'.
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    int l = s.length();
    int map = 0; // Map stores if we've seen a letter. First (binary) digit for 'a', second for 'b', etc.
    int n;
    for(int i = 0; i < l; i++){
        // Check if letter has appeared
        n = s[i]-97; // 'a' = 97, we want to map a=0, b=1, etc.
        // Check map's n'th digit to see if particular character has been seen or not
        if(map & (1 << n)){
            return false;
        }
        map = map ^ (1 << n); // XOR b/c if map was already 1, then we'd have returned false
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    // Argument handling
    if(argc != 2){
        cerr << "Usage: ./unique <string>" << endl;
        return -1;
    }
    string input = argv[1];
    // Main logic
    if(!(is_all_lowercase(input))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return -1;
    }
    if(all_unique_letters(input)){
        cout << "All letters are unique." << endl;
        return 0;
    } else {
        cout << "Duplicate letters found." << endl;
        return 0;
    }
}
