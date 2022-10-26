/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Jason Qiu
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 26 October 2022
 * Description   : Implements the quickselect algorithm.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    // TODO
    // DO NOT change the function header in any way, otherwise you will lose points.
    int p = array[left], temp;
    size_t s = left;
    for(size_t i = left+1; i <= right; i++){
        if(array[i] < p){
            s++;
            // Swap array[i], array[s]
            temp = array[i];
            array[i] = array[s];
            array[s] = temp;
        }
    }
    // Swap array[left], array[s]
    temp = array[left];
    array[left] = array[s];
    array[s] = temp;
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    // TODO
    // DO NOT change the function header in any way, otherwise you will lose points.
    size_t pivot_index = lomuto_partition(array, left, right);
    if(pivot_index == k - 1) return array[pivot_index];
    else if(pivot_index > k - 1) return quick_select(array, left, pivot_index - 1, k);
    else return quick_select(array, pivot_index + 1, right, k);
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
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

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    
    if(k > num_values){
        string values_or_value = (num_values == 1) ? " value." : " values." ;
        cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << values_or_value << endl;
        return 1;
    }

    // TODO - call the quick_select function and display the result
    int* array = new int[num_values];
    for(int i = 0; i < num_values; i++){
        array[i] = values[i];
    }
    int result = quick_select(array, 0, num_values-1, k);
    cout << "Smallest element " << k << ": " <<  result << endl;

    delete[] array;
    return 0;
}
