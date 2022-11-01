/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Jason Qiu
 * Version     : 1.0
 * Date        : 30 Oct 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
static long merge(int array[], int scratch[], int low, int mid, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0;
    int current;
    for(int i = 0; i < length; i++){
        current = array[i];
        for(int j = i+1; j < length; j++){
            if(array[j] < current){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length];
    long result = mergesort(array, scratch, 0, length-1);
    delete[] scratch;
    return result;
}

static long merge(int array[], int scratch[], int low, int mid, int high){
    int i = low, j = mid+1, k = low;
    long inversions = 0;
    while(i <= mid && j <= high){
        if(array[i] <= array[j]){
            scratch[k] = array[i];
            k++;
            i++;
        } else {
            scratch[k] = array[j];
            inversions += (mid-i) + 1;
            k++;
            j++;
        }
    }
    while(i <= mid){
        scratch[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        scratch[k] = array[j];
        k++;
        j++;
    }
    for(int i = low; i<= high; i++)
        array[i] = scratch[i];
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long inversions = 0;
    int mid = 0;
    if(low < high){
        mid = (low + high)/2;
        inversions += mergesort(array, scratch, low, mid);
        inversions += mergesort(array, scratch, mid + 1, high);
        inversions += merge(array, scratch, low, mid, high);
    }
    return inversions;
}
int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return -1;
    }
    if(argc == 2 && strcmp(argv[1], "slow") != 0){
        cout << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return -1;
    }
    bool slow = (argc == 2) ? true : false;

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    if(values.size() < 1){
        cerr << "Error: Sequence of integers not received." << endl;
        return -1;
    }

    // TODO: produce output
    if(slow)
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    else
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;

    return 0;
}
